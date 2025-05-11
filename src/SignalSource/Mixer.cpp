// Mixer.cpp
#include "Mixer.h"
#include <algorithm>

#define NUM_CHANNELS 32

Mixer::Mixer() : mSelectedChannel(0) {
  mChannels.reserve(NUM_CHANNELS);
  for (size_t i = 0; i < NUM_CHANNELS; ++i) {
    mChannels.push_back(std::make_shared<Channel>());
  }
}

Mixer::~Mixer() {}

void Mixer::setChannelSignalType(size_t channelIndex, size_t signalIndex,
                                 SignalType type) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setSignalType(signalIndex,
                                           type); // Default signal index 0
  }
}

void Mixer::setChannelFrequency(size_t channelIndex, size_t signalIndex,
                                float frequency) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setSignalFrequency(signalIndex, frequency);
  }
}

void Mixer::setChannelVolume(size_t channelIndex, size_t signalIndex,
                             float amplitude) {
  if (channelIndex < mChannels.size()) {
    mChannels[channelIndex]->setSignalAmplitude(signalIndex, amplitude);
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
    if (channel->isActive()) {
      output += channel->nextSample();
    }
  }
  output = normalizeOutput(output);

  return output;
}

std::pair<float, float> Mixer::nextSampleStereo() {
  float left = 0.0f;
  float right = 0.0f;
  for (auto &channel : mChannels) {
    if (channel->isActive()) {
      float sample = channel->nextSample();
      float pan = std::clamp(static_cast<float>(channel->getPosX()) / 100.0f,
                             0.0f, 1.0f);
      left += sample * (1.0f - pan);
      right += sample * pan;
    }
  }
  left = normalizeOutput(left);
  right = normalizeOutput(right);
  return {left, right};
}

std::vector<std::shared_ptr<Channel>> Mixer::getChannels() const {
  return mChannels;
}

float Mixer::normalizeOutput(float output) const {
  int activeCount = 0;
  for (auto &channel : mChannels) {
    if (channel->isActive())
      ++activeCount;
  }
  if (activeCount > 0) {
    output /= static_cast<float>(activeCount);
  }
  return output;
}