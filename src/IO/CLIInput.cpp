#include "CLIInput.h"
#include <iostream>

CLIInput::CLIInput() : mExit(false), mSelectedChannel(0), mSelectedSignal(0) {}

void CLIInput::processInput(SignalSource &signalSource) {
  std::cout << "\nComanda (q: exit, c<num>: canal, s<num>: senyal, a: activar, "
               "d: desactivar): ";
  std::string cmd;
  std::cin >> cmd;

  if (cmd == "q") {
    mExit = true;
  } else if (cmd[0] == 'c') {
    mSelectedChannel = cmd[1] - '0';
    std::cout << "Canal seleccionat: " << mSelectedChannel << std::endl;
  } else if (cmd[0] == 's') {
    mSelectedSignal = cmd[1] - '0';
    std::cout << "Senyal seleccionat: " << mSelectedSignal << std::endl;
  } else if (cmd == "a") {
    signalSource.getChannels()[mSelectedChannel]->activateChannel();
    std::cout << "Canal activat." << std::endl;
  } else if (cmd == "d") {
    signalSource.getChannels()[mSelectedChannel]->deactivateChannel();
    std::cout << "Canal desactivat." << std::endl;
  }
}

bool CLIInput::shouldExit() const { return mExit; }
