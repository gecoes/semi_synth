#include "Channel.h"
#include <iostream>

#define SAMPLE_RATE 48000

#define FADER_SAMPLE_LENGTH 500
constexpr float TIME_PER_SAMPLE = 1.0f / SAMPLE_RATE;

Channel::Channel()
    : mSignals(4, std::make_shared<SineWave>()), mPos_x(50), mPos_y(50),
      mFadeTarget(0.0f), mFadeCurrent(0.0f), mIsActive(false) {}

float Channel::updateFadeFactor() {
  const float fadeStep = 1.0f / FADER_SAMPLE_LENGTH;

  if (mFadeCurrent < mFadeTarget) {
    mFadeCurrent += fadeStep;
    if (mFadeCurrent > mFadeTarget) {
      mFadeCurrent = mFadeTarget;
    }
  } else if (mFadeCurrent > mFadeTarget) {
    mFadeCurrent -= fadeStep;
    if (mFadeCurrent < mFadeTarget) {
      mFadeCurrent = mFadeTarget;
    }
  }

  return mFadeCurrent;
}

Channel::~Channel() {}
float Channel::nextSample() {
  std::lock_guard<std::mutex> lock(mMutex);
  if (mSignals.empty()) {
    return 0.0f;
  }
  float signalOutput = 0.0f;
  for (auto &signal : mSignals) {
    signalOutput += signal->nextSample();
  }
  float fadeFactor = updateFadeFactor();

  if (std::abs(mFadeCurrent) < 0.0001f && mFadeTarget == 0.0f) {
    mIsActive = false; // Deactivate the channel if the fade-out is complete
  }
  return (signalOutput * fadeFactor) / mSignals.size();
}

float Channel::getSignalFrequency(size_t signalIndex) const {
  std::lock_guard<std::mutex> lock(mMutex);
  if (signalIndex < mSignals.size()) {
    return mSignals[signalIndex]->getFrequency();
  }
  return 0.0f;
}

float Channel::getSignalAmplitude(size_t signalIndex) const {
  std::lock_guard<std::mutex> lock(mMutex);
  if (signalIndex < mSignals.size()) {
    return mSignals[signalIndex]->getAmplitude();
  }
  return 0.0f;
}

void Channel::setSignalType(size_t signalIndex, SignalType type) {
  std::lock_guard<std::mutex> lock(mMutex);
  switch (type) {
  case SignalType::SINE:
    mSignals[signalIndex] =
        std::make_shared<SineWave>(mSignals[signalIndex]->getFrequency());
    break;
  case SignalType::SQUARE:
    mSignals[signalIndex] =
        std::make_shared<SquareWave>(mSignals[signalIndex]->getFrequency());
    break;
  case SignalType::SAW:
    mSignals[signalIndex] =
        std::make_shared<SawtoothWave>(mSignals[signalIndex]->getFrequency());
    break;
  case SignalType::SILENCE:
  default:
    mSignals[signalIndex] =
        std::make_shared<SilentSignal>(mSignals[signalIndex]->getFrequency());
    break;
  }
}

void Channel::activateChannel() {
  std::lock_guard<std::mutex> lock(mMutex);
  mFadeCurrent = 0;
  mFadeTarget = 1;
  mIsActive = true;
}
void Channel::deactivateChannel() {
  std::lock_guard<std::mutex> lock(mMutex);
  mFadeTarget = 0;
}

void Channel::setSignalFrequency(size_t signalIndex, float frequency) {
  std::lock_guard<std::mutex> lock(mMutex);
  if (mSignals[signalIndex]) {
    mSignals[signalIndex]->setFrequency(frequency);
  }
}
void Channel::setSignalAmplitude(size_t signalIndex, float volume) {
  std::lock_guard<std::mutex> lock(mMutex);
  mSignals[signalIndex]->setAmplitude(volume);
}
void Channel::setPosX(size_t x) {
  std::lock_guard<std::mutex> lock(mMutex);
  mPos_x = x;
}
void Channel::setPosY(size_t y) {
  std::lock_guard<std::mutex> lock(mMutex);
  mPos_y = y;
}
size_t Channel::getPosX() const {
  std::lock_guard<std::mutex> lock(mMutex);
  return mPos_x;
}
size_t Channel::getPosY() const {
  std::lock_guard<std::mutex> lock(mMutex);
  return mPos_y;
}
