#include "Signal.h"

#include <cmath>
#include <iostream>

#define DEFAULT_FREQUENCY 1000
#define DEFAULT_AMPLITUDE 1

Signal::Signal()
    : mFrequency(DEFAULT_FREQUENCY), mAmplitude(DEFAULT_AMPLITUDE) {}

Signal::Signal(float frequency)
    : mFrequency(frequency), mAmplitude(DEFAULT_AMPLITUDE) {}

Signal::~Signal() {}

void Signal::setFrequency(float frequency) { mFrequency = frequency; }

void Signal::setAmplitude(float amplitude) { mAmplitude = amplitude; }

float Signal::getFrequency() const { return mFrequency; }

float Signal::getAmplitude() const { return mAmplitude; }

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
  float sample = mAmplitude * (2.0f * (timeInLoop * mFrequency -
                                       floor(0.5f + timeInLoop * mFrequency)));
  return sample;
}
