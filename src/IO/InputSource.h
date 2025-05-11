// InputSource.h
#ifndef INPUTSOURCE_H
#define INPUTSOURCE_H

#include "SignalSource.h"

class InputSource {
public:
  virtual ~InputSource() = default;

  // Process input and modify the mixer accordingly
  virtual void processInput(SignalSource &signalSoruce) = 0;

  // State for edit mode
  virtual bool isEditMode() const = 0;
  virtual int getSelectedChannel() const = 0;
};

#endif // INPUTSOURCE_H
