#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <cmath>

#define SAMPLE_RATE 48000
#define BARS 8
#define TIME 4 // Number of pulses per bar
#define STEPS 16
#define BPM 120

class Transport {
public:
  Transport() {}
  ~Transport() {}
  void advance();

private:
  float mGlobalTime;
  float mTimeInLoop;
  float const mLoopLength = (BARS * TIME) / (BPM / 60.0f);
};

#endif // TRANSPORT_H