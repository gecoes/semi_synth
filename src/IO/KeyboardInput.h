// KeyboardInput.h
#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "InputSource.h"
#include <string>

class KeyboardInput : public InputSource {
public:
  KeyboardInput();

  void processInput(SignalSource &signalSource) override;
  bool isEditMode() const override;
  int getSelectedChannel() const override;
  bool shouldExit() const;

private:
  bool mEditMode;
  int mSelectedChannel;
  int mSelectedSignal;
  bool mExit;
};

#endif // KEYBOARDINPUT_H