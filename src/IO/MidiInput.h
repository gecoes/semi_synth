// MidiInput.h
#ifndef MIDI_INPUT_H
#define MIDI_INPUT_H

#include "InputSource.h"
#include <RtMidi.h>
#include <memory>
#include <optional>
#include <set>
#include <vector>

class MidiInput : public InputSource
{
public:
  MidiInput();
  ~MidiInput();

  void processInput(SignalSource &signalSource) override;
  bool isEditMode() const override;
  int getSelectedChannel() const override;
  bool shouldExit() const;

private:
  void handleMidiMessage(double deltaTime, std::vector<unsigned char> *message);
  static void midiCallback(double deltaTime,
                           std::vector<unsigned char> *message, void *userData);
  static std::optional<int> mapNoteToChannel(int midiNote);

  static float midiNoteToFrequency(int midiNote);

  std::unique_ptr<RtMidiIn> mMidiIn;
  std::set<int> mActiveNotes;
  SignalSource *mSignalSource; // Only used within callback context
  bool mExit;
};

#endif // MIDI_INPUT_H
