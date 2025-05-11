// SignalSource.h
#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "Channel.h"
#include <memory>
#include <vector>

class SignalSource {
public:
  virtual float nextSample(float sampleRate) = 0;
  virtual std::pair<float, float> nextSampleStereo() = 0;
  virtual void reset() {}
  virtual ~SignalSource() = default;

  virtual std::vector<std::shared_ptr<Channel>> getChannels() const = 0;
  virtual void setChannelFrequency(size_t channelIndex, size_t signalIndex,
                                   float frequency) = 0;
  virtual void setChannelVolume(size_t channelIndex, size_t signalIndex,
                                float amplitude) = 0;
  virtual void setChannelPosX(size_t channelIndex, size_t x) = 0;
  virtual void setChannelPosY(size_t channelIndex, size_t y) = 0;
  virtual void setChannelSignalType(size_t channelIndex, size_t signalIndex,
                                    SignalType type) = 0;
};

#endif // SIGNALSOURCE_H