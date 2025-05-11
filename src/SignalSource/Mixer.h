#ifndef MIXER_H
#define MIXER_H

#include "SignalSource.h"
#include <iostream>
#include <memory>
#include <vector>

class Mixer : public SignalSource {
public:
  Mixer();
  ~Mixer() override;

  float nextSample(float sampleRate) override;
  std::pair<float, float> nextSampleStereo() override;
  std::vector<std::shared_ptr<Channel>> getChannels() const override;

  void setChannelSignalType(size_t channelIndex, size_t signalIndex,
                            SignalType type) override;
  void setChannelFrequency(size_t channelIndex, size_t signalIndex,
                           float frequency) override;
  void setChannelVolume(size_t channelIndex, size_t signalIndex,
                        float amplitude) override;
  void setChannelPosX(size_t channelIndex, size_t x) override;
  void setChannelPosY(size_t channelIndex, size_t y) override;

private:
  float normalizeOutput(float output) const;
  std::vector<std::shared_ptr<Channel>> mChannels;
  size_t mSelectedChannel;
};

#endif // MIXER_H