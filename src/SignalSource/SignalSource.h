#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "Channel.h"
#include <memory>

class SignalSource {
public:
  virtual float nextSample(float sampleRate) = 0;
  virtual void reset() {}
  virtual ~SignalSource() = default;
  virtual void setFrequency(size_t frequency) = 0;
  virtual void setAmplitude(size_t amplitude) = 0;
};

#endif // SIGNALSOURCE_H