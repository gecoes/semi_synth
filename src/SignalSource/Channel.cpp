#include "Channel.h"
#include <iostream>

#define FADER_SAMPLE_LENGTH 500
constexpr float TIME_PER_SAMPLE = 1.0f / SAMPLE_RATE;
constexpr float STEP_LENGTH = LOOP_LENGTH / PULSES;
constexpr float STEP_SAMPLES = STEP_LENGTH / TIME_PER_SAMPLE;

Channel::Channel()
    : mSignal(std::make_shared<SilentSignal>()), mVolume(0.0f), mPos_x(0),
      mPos_y(0) {
  mPattern.fill(true);
}

Channel::~Channel() {}
float Channel::nextSample(float timeInLoop) {
  int currentStep =
      static_cast<int>((timeInLoop / LOOP_LENGTH) * PULSES) % PULSES;

  bool patternChanged = (currentStep + 1 < mPattern.size()) &&
                        (mPattern[currentStep] != mLastPatternState ||
                         mPattern[currentStep] != mPattern[currentStep + 1]);
  mLastPatternState = mPattern[currentStep];

  float fadeFactor = patternChanged ? calculateFadeFactor(timeInLoop) : 1.0f;

  return mPattern[currentStep] ? mSignal->nextSample(timeInLoop) * fadeFactor
                               : 0.0f;
}

float Channel::calculateFadeFactor(float timeInLoop) {
  float sampleInStep = calculateCurrentSampleInStep(timeInLoop);
  if (sampleInStep <= FADER_SAMPLE_LENGTH) {
    return sampleInStep / FADER_SAMPLE_LENGTH;
  } else if (sampleInStep >= STEP_SAMPLES - FADER_SAMPLE_LENGTH) {
    return (STEP_SAMPLES - sampleInStep) / FADER_SAMPLE_LENGTH;
  }
  return 1.0f;
}

size_t Channel::calculateCurrentSampleInStep(float timeInLoop) {
  size_t sampleInLoop = static_cast<size_t>(timeInLoop * SAMPLE_RATE);
  return sampleInLoop % static_cast<int>(STEP_SAMPLES);
}

void Channel::setSignalType(SignalType type) {
  switch (type) {
  case SignalType::SINE:
    mSignal = std::make_shared<SineWave>();
    break;
  case SignalType::SQUARE:
    mSignal = std::make_shared<SquareWave>();
    break;
  case SignalType::SAW:
    mSignal = std::make_shared<SawtoothWave>();
    break;
  case SignalType::SILENCE:
  default:
    mSignal = std::make_shared<SilentSignal>();
    break;
  }
}
void Channel::updatePatternStep(bool stepState, float timeInLoop) {
  int currentStep = static_cast<int>((timeInLoop / 8.0) * PULSES) % PULSES;
  mPattern[currentStep] = stepState;
}

void Channel::setPattern(const std::array<bool, PULSES> &pattern) {
  mPattern = pattern;
}
void Channel::setFrequency(size_t frequency) {
  if (mSignal) {
    mSignal->setFrequency(frequency);
  }
}
void Channel::setVolume(float volume) { mVolume = volume; }
void Channel::setPosX(size_t x) { mPos_x = x; }
void Channel::setPosY(size_t y) { mPos_y = y; }
float Channel::getVolume() const { return mVolume; }
size_t Channel::getPosX() const { return mPos_x; }
size_t Channel::getPosY() const { return mPos_y; }
void Channel::reset() {
  mSignal = nullptr;
  mVolume = 0.0f;
  mPos_x = 0;
  mPos_y = 0;
  mPattern.fill(false);
}