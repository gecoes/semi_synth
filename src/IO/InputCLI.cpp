
#include "InputCLI.h"
#include <limits>

CLIInput::CLIInput()
    : mEditMode(false), mSelectedChannel(0), mSelectedSignal(0) {}

void CLIInput::processInput(SignalSource &signalSoruce) {
  std::string line;
  std::cout
      << "Input (e: edit, p: play, s: signal idx, f: freq, v: vol, t: type): ";
  std::getline(std::cin, line);
  std::istringstream iss(line);
  std::string cmd;
  iss >> cmd;

  if (cmd == "e") {
    int ch;
    iss >> ch;
    if (ch >= 0 && ch < static_cast<int>(signalSoruce.getChannels().size())) {
      mSelectedChannel = ch;
      mEditMode = true;
      signalSoruce.getChannels()[ch]->activateChannel();
    }
  } else if (cmd == "p") {
    int ch;
    iss >> ch;
    if (ch >= 0 && ch < static_cast<int>(signalSoruce.getChannels().size())) {
      signalSoruce.getChannels()[ch]->activateChannel();
    }
  } else if (cmd == "s") {
    int sig;
    iss >> sig;
    mSelectedSignal = sig;
  } else if (cmd == "f" && mEditMode) {
    float freq;
    iss >> freq;
    signalSoruce.getChannels()[mSelectedChannel]->setSignalFrequency(
        mSelectedSignal, freq);
  } else if (cmd == "v" && mEditMode) {
    float vol;
    iss >> vol;
    signalSoruce.getChannels()[mSelectedChannel]->setSignalAmplitude(
        mSelectedSignal, vol);
  } else if (cmd == "t" && mEditMode) {
    std::string type;
    iss >> type;
    SignalType signalType = SignalType::SINE;
    if (type == "sine")
      signalType = SignalType::SINE;
    else if (type == "square")
      signalType = SignalType::SQUARE;
    else if (type == "saw")
      signalType = SignalType::SAW;
    else if (type == "silence")
      signalType = SignalType::SILENCE;
    signalSoruce.getChannels()[mSelectedChannel]->setSignalType(mSelectedSignal,
                                                                signalType);
  }
}

bool CLIInput::isEditMode() const { return mEditMode; }

int CLIInput::getSelectedChannel() const { return mSelectedChannel; }
