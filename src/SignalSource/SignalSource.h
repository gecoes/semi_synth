#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "Channel.h"
#include <memory>

class SignalSource {
public:
  virtual float nextSample(float sampleRate) = 0;
  virtual void reset() {}
  virtual ~SignalSource() = default;
};

#endif // SIGNALSOURCE_H