#ifndef CLI_INPUT_H
#define CLI_INPUT_H

#include "SignalSource.h"

class CLIInput {
public:
  CLIInput();
  void processInput(SignalSource &signalSource);
  bool shouldExit() const;

private:
  bool mExit;
  int mSelectedChannel;
  int mSelectedSignal;
};

#endif // CLI_INPUT_H