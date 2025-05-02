#include "Transport.h"

Transport::Transport() : mGlobalTime(0.0f), mTimeInLoop(0.0f) {}
Transport::~Transport() {}

size_t Transport::getSampleRate() const { return mSampleRate; }
float Transport::getInLoop() const { return mTimeInLoop; }
void Transport::advance() {
  mGlobalTime += 1.0f / mSampleRate;
  mTimeInLoop = fmod(mGlobalTime, mLoopLength);
}