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
void Mixer::setChannelSignalType(size_t channelIndex, SignalType type) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setSignalType(type);
  }
}

void Mixer::setChannelPattern(size_t channelIndex,
                              const std::array<bool, PULSES> &pattern) {
  mChannels[channelIndex]->setPattern(pattern);
}
void Mixer::updateChannelPatternStep(size_t channelIndex, bool stepState,
                                     float timeInLoop) {
  mChannels[channelIndex]->updatePatternStep(stepState, timeInLoop);
}

void Mixer::setChannelFrequency(size_t channelIndex, size_t frequency) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setFrequency(frequency);
  }
}
void Mixer::setChannelVolume(size_t channelIndex, size_t amplitude) {
  mChannels[channelIndex]->setVolume(amplitude);
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
float Mixer::nextSample(float timeInLoop) {
  float output = 0.0f;
  for (auto &channel : mChannels) {
    output += channel->nextSample(timeInLoop);
  }
  return output;
}
std::pair<float, float> Mixer::nextSampleStereo(float timeInLoop) {
  float left = 0.0f;
  float right = 0.0f;
  for (auto &channel : mChannels) {
    float sample = channel->nextSample(timeInLoop);
    left += sample * (1 - channel->getPosX());
    right += sample * channel->getPosX();
  }
  return {left, right};
}
std::vector<std::shared_ptr<Channel>> Mixer::getChannels() const {
  return mChannels;
}