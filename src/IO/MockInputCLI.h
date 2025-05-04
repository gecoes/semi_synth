#ifndef MOCK_INPUT_CLI_H
#define MOCK_INPUT_CLI_H

#include "SignalSource.h"
#include <memory>

class MockInputCLI {

public:
  MockInputCLI() = default;
  MockInputCLI(std::shared_ptr<SignalSource> signalSource);

  ~MockInputCLI() = default;
  void setSignalSource(std::shared_ptr<SignalSource> signalSource);
  void updateFrequency(size_t frequency, size_t channelIndex);
  void updateAmplitude(size_t amplitude, size_t channelIndex);
  void updatePosX(size_t x, size_t channelIndex);
  void updatePosY(size_t y, size_t channelIndex);
  void updateSignalType(SignalType type, size_t channelIndex);

private:
  std::shared_ptr<SignalSource> mSignalSource;
};

#endif // MOCK_INPUT_CLI_H