#ifndef MIXER_H
#define MIXER_H

#include "SignalSource.h"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

class Mixer : public SignalSource {
public:
  Mixer();
  ~Mixer() override;

  float nextSample(float sampleRate) override;
  void reset() override;
  void setChannelFrequency(size_t channelIndex, size_t frequency);
  void setChannelVolume(size_t channelIndex, size_t amplitude);
  void setChannelPosX(size_t channelIndex, size_t x);
  void setChannelPosY(size_t channelIndex, size_t y);

private:
  std::vector<std::shared_ptr<Channel>> mChannels;
  size_t mSelectedChannel;
};

#endif // MIXER_H