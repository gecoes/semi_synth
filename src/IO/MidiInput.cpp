#include "MidiInput.h"
#include <cmath>
#include <iostream>
#include <optional>

MidiInput::MidiInput() : mExit(false), mSignalSource(nullptr)
{
  try
  {
    mMidiIn = std::make_unique<RtMidiIn>();

    unsigned int nPorts = mMidiIn->getPortCount();
    std::cout << "Initializing MIDI input..." << std::endl;
    std::cout << "Found " << nPorts << " MIDI port(s)." << std::endl;

    for (unsigned int i = 0; i < nPorts; ++i)
    {
      std::string name = mMidiIn->getPortName(i);
      std::cout << "  Port " << i << ": " << name << std::endl;
    }

    if (nPorts > 1)
    {
      mMidiIn->openPort(1); // ⬅️ o permetre triar dinàmicament
      std::cout << "MIDI input listening on port 1..." << std::endl;
    }
    else if (nPorts > 0)
    {
      mMidiIn->openPort(0);
      std::cout << "MIDI input listening on port 0..." << std::endl;
    }
    else
    {
      std::cerr << "No MIDI ports found." << std::endl;
    }

    mMidiIn->ignoreTypes(false, false, false);
    mMidiIn->setCallback(&MidiInput::midiCallback, this);
  }
  catch (RtMidiError &e)
  {
    std::cerr << "MIDI Init Error: " << e.getMessage() << std::endl;
    mExit = true;
  }
}

MidiInput::~MidiInput()
{
  if (mMidiIn && mMidiIn->isPortOpen())
  {
    mMidiIn->closePort();
  }
}

void MidiInput::processInput(SignalSource &signalSource)
{
  mSignalSource = &signalSource;
}

bool MidiInput::shouldExit() const { return mExit; }

void MidiInput::midiCallback(double deltaTime,
                             std::vector<unsigned char> *message,
                             void *userData)
{
  if (!message || message->empty())
    return;

  auto *self = static_cast<MidiInput *>(userData);
  self->handleMidiMessage(deltaTime, message);
}

void MidiInput::handleMidiMessage(double /*deltaTime*/,
                                  std::vector<unsigned char> *message)
{
  if (!mSignalSource || message->size() < 3)
    return;

  unsigned char status = message->at(0);
  unsigned char data1 = message->at(1);
  unsigned char data2 = message->at(2);

  bool isNoteOn = (status & 0xF0) == 0x90 && data2 > 0;
  bool isNoteOff =
      ((status & 0xF0) == 0x80) || ((status & 0xF0) == 0x90 && data2 == 0);

  auto channelOpt = mapNoteToChannel(data1);
  if (!channelOpt.has_value())
    return;

  int channel = channelOpt.value();

  if (isNoteOn)
  {
    mSignalSource->getChannels()[channel]->setSignalFrequency(
        0, midiNoteToFrequency(data1));
    mSignalSource->getChannels()[channel]->activateChannel();
    mActiveNotes.insert(channel);
    std::cout << "[MIDI] Note ON - Channel " << channel << std::endl;
  }
  else if (isNoteOff)
  {
    mSignalSource->getChannels()[channel]->deactivateChannel();
    mActiveNotes.erase(channel);
    std::cout << "[MIDI] Note OFF - Channel " << channel << std::endl;
  }
}

std::optional<int> MidiInput::mapNoteToChannel(int midiNote)
{
  constexpr int baseNote = 48;
  constexpr int channelCount = 32;
  if (midiNote < baseNote || midiNote >= baseNote + channelCount)
    return std::nullopt;
  return midiNote - baseNote;
}

float MidiInput::midiNoteToFrequency(int midiNote)
{
  return 440.0f * std::pow(2.0f, (midiNote - 69) / 12.0f);
}

bool MidiInput::isEditMode() const { return true; }

int MidiInput::getSelectedChannel() const { return -1; }