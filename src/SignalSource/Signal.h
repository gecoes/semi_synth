#ifndef SIGNAL_H
#define SIGNAL_H

class Signal {
public:
  Signal(){};
  virtual ~Signal(){};
  virtual float nextSample(float timeInLoop) = 0;
  virtual void reset() = 0;
  void setFrequency(size_t frequency);
  void setAmplitude(size_t amplitude);
  size_t getFrequency() const;
  size_t getAmplitude() const;

protected:
  size_t mFrequency;
  size_t mAmplitude;
};

enum class SignalType { SINE, SQUARE, SAW, SILENCE };

class SineWave : public Signal {
public:
  SineWave() : Signal() {}
  ~SineWave() override {}
  float nextSample(float timeInLoop) override;
};

class SquareWave : public Signal {
public:
  SquareWave() : Signal() {}
  ~SquareWave() override {}
  float nextSample(float timeInLoop) override;
};

class SawtoothWave : public Signal {
public:
  SawtoothWave() : Signal() {}
  ~SawtoothWave() override {}
  float nextSample(float timeInLoop) override;
};

class SilentSignal : public Signal {
public:
  SilentSignal() : Signal() {}
  ~SilentSignal() override {}
  float nextSample(float timeInLoop) override { return 0.0f; }
};

#endif