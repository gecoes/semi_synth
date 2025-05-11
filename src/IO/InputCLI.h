// CLIInput.h
#ifndef CLIINPUT_H
#define CLIINPUT_H

#include "InputSource.h"
#include <iostream>
#include <sstream>
#include <string>

class CLIInput : public InputSource {
public:
  CLIInput();

  void processInput(SignalSource &signalSource) override;
  bool isEditMode() const override;
  int getSelectedChannel() const override;

private:
  bool mEditMode;
  int mSelectedChannel;
  int mSelectedSignal;
};

#endif // CLIINPUT_H