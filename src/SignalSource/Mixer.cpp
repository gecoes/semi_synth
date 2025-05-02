#include "Mixer.h"

#define NUM_CHANNELS 4

Mixer::Mixer() : mSelectedChannel(0) {
  for (size_t i = 0; i < NUM_CHANNELS; ++i) {
    mChannels.push_back(std::make_shared<Channel>());
  }
}
Mixer::~Mixer() {
  for (auto &channel : mChannels) {
    channel->reset();
  }
}
void Mixer::setChannelFrequency(size_t channelIndex, size_t frequency) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setFrequency(frequency);
  }
}
void Mixer::setChannelVolume(size_t channelIndex, size_t amplitude) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setVolume(amplitude);
  }
}
void Mixer::setChannelPosX(size_t channelIndex, size_t x) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setPosX(x);
  }
}
void Mixer::setChannelPosY(size_t channelIndex, size_t y) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setPosY(y);
  }
}
float Mixer::nextSample(float sampleRate) {
  float output = 0.0f;
  for (auto &channel : mChannels) {
    output += channel->nextSample(sampleRate);
  }
  return output;
}