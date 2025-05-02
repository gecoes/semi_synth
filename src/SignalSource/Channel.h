#ifndef CHANNEL_H
#define CHANNEL_H

#include "Signal.h"
#include "Transport.h"
#include <array>
#include <iostream>
#include <memory>

class Channel {
public:
  Channel();
  ~Channel();
  float nextSample(float timeInLoop);
  void setSignalType(SignalType type);
  void setPattern(const std::array<bool, PULSES> &pattern);
  void updatePatternStep(bool stepState, float timeInLoop);
  void setFrequency(size_t frequency);
  void setVolume(float volume);
  void setPosX(size_t x);
  void setPosY(size_t y);
  float getVolume() const;
  size_t getPosX() const;
  size_t getPosY() const;
  void reset();

private:
  float calculateFadeFactor(float timeInLoop);
  size_t calculateCurrentSampleInStep(float timeInLoop);
  std::shared_ptr<Signal> mSignal;
  std::array<bool, PULSES> mPattern;
  float mVolume;
  bool mLastPatternState;
  size_t mPos_x;
  size_t mPos_y;
};
#endif