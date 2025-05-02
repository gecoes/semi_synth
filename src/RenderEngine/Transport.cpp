#include "Transport.h"

Transport::Transport() : mGlobalTime(0.0f), mTimeInLoop(0.0f) {}
Transport::~Transport() {}
void Transport::advance() {
  mGlobalTime += 1.0f / SAMPLE_RATE;
  mTimeInLoop = fmod(mGlobalTime, mLoopLength);
}