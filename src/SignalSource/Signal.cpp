#include "Signal.h"

#include <cmath>
#include <iostream>

#define DEFAULT_FREQUENCY 1000
#define DEFAULT_AMPLITUDE 0

Signal::Signal()
    : mFrequency(DEFAULT_FREQUENCY), mAmplitude(DEFAULT_AMPLITUDE) {}

Signal::~Signal() {}

void Signal::setFrequency(size_t frequency) { mFrequency = frequency; }

void Signal::setAmplitude(size_t amplitude) { mAmplitude = amplitude; }

size_t Signal::getFrequency() const { return mFrequency; }

size_t Signal::getAmplitude() const { return mAmplitude; }

float SineWave::nextSample(float timeInLoop) {
  float sample = mAmplitude * sin(2.0f * M_PI * mFrequency * timeInLoop);
  return sample;
}

float SquareWave::nextSample(float timeInLoop) {
  float sample =
      mAmplitude *
      (sin(2.0f * M_PI * mFrequency * timeInLoop) >= 0 ? 1.0f : -1.0f);
  return sample;
}

float SawtoothWave::nextSample(float timeInLoop) {
  float sample =
      (2.0f * mAmplitude / M_PI) * (timeInLoop - floor(timeInLoop + 0.5f));
  return sample;
}
