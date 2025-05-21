#ifndef SIGNAL_H
#define SIGNAL_H
#include <cstddef>
#include <string>

enum class SignalType { SINE, SQUARE, SAW, SILENCE };
class Signal {
public:
  Signal();
  Signal(float frequency);
  Signal(Signal const &other) = default;
  virtual ~Signal();
  virtual float nextSample() = 0;
  virtual void reset() = 0;
  std::string getSignalType() const;
  void setFrequency(float frequency);
  void setAmplitude(float amplitude);
  float getFrequency() const;
  float getAmplitude() const;

protected:
  void updatePhase();
  float mFrequency;
  float mAmplitude;
  float mPhase;
  float mSampleRate;
  SignalType mSignalType;
};

class SineWave : public Signal {
public:
  SineWave() : Signal() { mSignalType = SignalType::SINE; }
  SineWave(float frequency) : Signal(frequency) {
    mSignalType = SignalType::SINE;
  }
  SineWave(SineWave const &other) : Signal(other) {}
  ~SineWave() override {}
  void reset() override {}
  float nextSample() override;
};

class SquareWave : public Signal {
public:
  SquareWave() : Signal() { mSignalType = SignalType::SQUARE; }
  SquareWave(float frequency) : Signal(frequency) {
    mSignalType = SignalType::SQUARE;
  }
  SquareWave(SquareWave const &other) : Signal(other) {}
  ~SquareWave() override {}
  void reset() override {}
  float nextSample() override;
};

class SawtoothWave : public Signal {
public:
  SawtoothWave() : Signal() { mSignalType = SignalType::SAW; }
  SawtoothWave(float frequency) : Signal(frequency) {
    mSignalType = SignalType::SAW;
  }
  SawtoothWave(SawtoothWave const &other) : Signal(other) {}
  ~SawtoothWave() override {}
  void reset() override {}
  float nextSample() override;
};

class SilentSignal : public Signal {
public:
  SilentSignal() : Signal() { mSignalType = SignalType::SILENCE; }
  SilentSignal(float frequency) : Signal(frequency) {
    mSignalType = SignalType::SILENCE;
  }
  SilentSignal(SilentSignal const &other) : Signal(other) {}
  ~SilentSignal() override {}
  void reset() override {}
  float nextSample() override { return 0.0f; }
};

#endif