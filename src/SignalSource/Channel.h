#ifndef CHANNEL_H
#define CHANNEL_H

#include "Signal.h"
#include "Transport.h"
#include <array>
#include <iostream>
#include <memory>

class Channel {
public:
  Channel() {}
  float nextSample(float timeInLoop);
  void setSignalType(SignalType type, float freq);
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
  std::shared_ptr<Signal> mSignal;
  std::array<bool, BARS * TIME> mPattern;
  float mVolume;
  size_t mPos_x;
  size_t mPos_y;
};
#endif