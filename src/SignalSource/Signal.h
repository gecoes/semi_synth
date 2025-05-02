#ifndef SIGNAL_H
#define SIGNAL_H
#include <cstddef>

class Signal {
public:
  Signal();
  Signal(float frequency);
  Signal(Signal const &other) = default;
  virtual ~Signal();
  virtual float nextSample(float timeInLoop) = 0;
  virtual void reset() = 0;
  void setFrequency(float frequency);
  void setAmplitude(float amplitude);
  float getFrequency() const;
  float getAmplitude() const;

protected:
  float mFrequency;
  float mAmplitude;
};

enum class SignalType { SINE, SQUARE, SAW, SILENCE };

class SineWave : public Signal {
public:
  SineWave() : Signal() {}
  SineWave(float frequency) : Signal(frequency) {}
  SineWave(SineWave const &other) : Signal(other) {}
  ~SineWave() override {}
  void reset() override {}
  float nextSample(float timeInLoop) override;
};

class SquareWave : public Signal {
public:
  SquareWave() : Signal() {}
  SquareWave(float frequency) : Signal(frequency) {}
  SquareWave(SquareWave const &other) : Signal(other) {}
  ~SquareWave() override {}
  void reset() override {}
  float nextSample(float timeInLoop) override;
};

class SawtoothWave : public Signal {
public:
  SawtoothWave() : Signal() {}
  SawtoothWave(float frequency) : Signal(frequency) {}
  SawtoothWave(SawtoothWave const &other) : Signal(other) {}
  ~SawtoothWave() override {}
  void reset() override {}
  float nextSample(float timeInLoop) override;
};

class SilentSignal : public Signal {
public:
  SilentSignal() : Signal() {}
  SilentSignal(float frequency) : Signal(frequency) {}
  SilentSignal(SilentSignal const &other) : Signal(other) {}
  ~SilentSignal() override {}
  void reset() override {}
  float nextSample(float timeInLoop) override { return 0.0f; }
};

#endif