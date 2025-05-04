#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "Channel.h"
#include <memory>

class SignalSource {
public:
  virtual float nextSample(float sampleRate) = 0;
  virtual std::pair<float, float> nextSampleStereo(float timeInLoop) = 0;
  virtual void reset() {}
  virtual ~SignalSource() = default;
  virtual void setChannelFrequency(size_t channelIndex, size_t frequency) = 0;
  virtual void setChannelVolume(size_t channelIndex, size_t amplitude) = 0;
  virtual void setChannelPosX(size_t channelIndex, size_t x) = 0;
  virtual void setChannelPosY(size_t channelIndex, size_t y) = 0;
  virtual void setChannelSignalType(size_t channelIndex, SignalType type) = 0;
  virtual void setChannelPattern(size_t channelIndex,
                                 const std::array<bool, PULSES> &pattern) = 0;
  virtual void updateChannelPatternStep(size_t channelIndex, bool stepState,
                                        float timeInLoop) = 0;
};

#endif // SIGNALSOURCE_H