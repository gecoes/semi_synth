#ifndef CHANNEL_H
#define CHANNEL_H

#include "Signal.h"
#include <array>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

class Channel {
public:
  Channel();
  ~Channel();
  float nextSample();
  bool isActive() const { return mIsActive; }
  void activateChannel();
  void deactivateChannel();
  void setSignalType(size_t signalIndex, SignalType type);
  void setSignalFrequency(size_t signalIndex, float frequency);
  void setSignalAmplitude(size_t signalIndex, float volume);
  void setPosX(size_t x);
  void setPosY(size_t y);
  std::shared_ptr<Signal> getSignal(size_t signalIndex) const;
  float getSignalFrequency(size_t signalIndex) const;
  float getSignalAmplitude(size_t signalIndex) const;
  float getVolume() const;
  size_t getPosX() const;
  size_t getPosY() const;
  void reset();

private:
  float updateFadeFactor();
  std::vector<std::shared_ptr<Signal>> mSignals;
  mutable std::mutex mMutex;
  float mFadeTarget;
  float mFadeCurrent;
  bool mIsActive;
  size_t mPos_x;
  size_t mPos_y;
};
#endif