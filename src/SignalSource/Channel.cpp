#include "Channel.h"

Channel::Channel()
    : mSignal(std::make_shared<SilentSignal>()), mVolume(0.0f), mPos_x(0),
      mPos_y(0) {
  mPattern.fill(true);
}

Channel::~Channel() {}
float Channel::nextSample(float timeInLoop) {
  int currentStep = static_cast<int>((timeInLoop / 8.0) * STEPS) % STEPS;
  return mSignal->nextSample(timeInLoop) ? !mPattern[currentStep] : 0.0f;
}

void Channel::setSignalType(SignalType type, float freq) {
  switch (type) {
  case SignalType::SINE:
    mSignal = std::make_shared<SineWave>(freq);
    break;
  case SignalType::SQUARE:
    mSignal = std::make_shared<SquareWave>(freq);
    break;
  case SignalType::SAW:
    mSignal = std::make_shared<SawtoothWave>(freq);
    break;
  case SignalType::SILENCE:
  default:
    mSignal = std::make_shared<SilentSignal>();
    break;
  }
}
void Channel::setPattern(const std::array<bool, BARS * TIME> &pattern) {
  mPattern = pattern;
}
void Channel::updatePatternStep(bool stepState, float timeInLoop) {
  int currentStep = static_cast<int>((timeInLoop / 8.0) * STEPS) % STEPS;
  mPattern[currentStep] = stepState;
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