#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <cmath>

#define SAMPLE_RATE 48000.0f
#define BARS 8.0f
#define TIME 4.0f // Number of pulses per bar
#define PULSES 256
#define BPM 120.0f
#define LOOP_LENGTH 16.0f

class Transport {
public:
  Transport();
  ~Transport();
  size_t getSampleRate() const;
  float getInLoop() const;
  void advance();

private:
  float mGlobalTime;
  float mTimeInLoop;
  float const mLoopLength = LOOP_LENGTH;
  size_t const mSampleRate = SAMPLE_RATE;
};

#endif // TRANSPORT_H