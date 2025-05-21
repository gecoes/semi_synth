#include "Signal.h"

#include <cmath>
#include <iostream>

#define DEFAULT_FREQUENCY 1000
#define DEFAULT_AMPLITUDE 1
#define DEFAULT_SAMPLE_RATE 48000

Signal::Signal()
    : mFrequency(DEFAULT_FREQUENCY), mAmplitude(DEFAULT_AMPLITUDE),
      mSampleRate(DEFAULT_SAMPLE_RATE), mPhase(0) {}

Signal::Signal(float frequency)
    : mFrequency(frequency), mAmplitude(DEFAULT_AMPLITUDE),
      mSampleRate(DEFAULT_SAMPLE_RATE), mPhase(0) {}

Signal::~Signal() {}

void Signal::setFrequency(float frequency) { mFrequency = frequency; }

void Signal::setAmplitude(float amplitude) {
  mAmplitude = amplitude <= 1.0f ? amplitude : 1.0f;
}

float Signal::getFrequency() const { return mFrequency; }

float Signal::getAmplitude() const { return mAmplitude; }

std::string Signal::getSignalType() const {
  switch (mSignalType) {
  case SignalType::SINE:
    return "sin";
  case SignalType::SQUARE:
    return "square";
  case SignalType::SAW:
    return "saw";
  default:
    return "unknown";
  }
}

void Signal::updatePhase() {
  mPhase += 2.0f * M_PI * mFrequency / mSampleRate;
  if (mPhase >= 2.0f * M_PI)
    mPhase -= 2.0f * M_PI;
}

float SineWave::nextSample() {
  float sample = mAmplitude * sin(mPhase);
  updatePhase();
  return sample;
}

float SquareWave::nextSample() {
  float sample = mAmplitude * (sin(mPhase) >= 0 ? 1.0f : -1.0f);
  updatePhase();
  return sample;
}

float SawtoothWave::nextSample() {
  float sample = mAmplitude * (mPhase / M_PI - 1.0f);
  updatePhase();
  return sample;
}
