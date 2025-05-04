#include "MockInputCLI.h"
#include "SignalSource.h"

MockInputCLI::MockInputCLI(std::shared_ptr<SignalSource> signalSource)
    : mSignalSource(signalSource) {}
void MockInputCLI::updateFrequency(size_t frequency, size_t channelIndex) {
  if (mSignalSource) {
    mSignalSource->setChannelFrequency(channelIndex, frequency);
  }
}
void MockInputCLI::updateAmplitude(size_t amplitude, size_t channelIndex) {
  if (mSignalSource) {
    mSignalSource->setChannelVolume(channelIndex, amplitude);
  }
}
void MockInputCLI::updatePosX(size_t x, size_t channelIndex) {
  if (mSignalSource) {
    mSignalSource->setChannelPosX(channelIndex, x);
  }
}
void MockInputCLI::updatePosY(size_t y, size_t channelIndex) {
  if (mSignalSource) {
    mSignalSource->setChannelPosY(channelIndex, y);
  }
}
void MockInputCLI::updateSignalType(SignalType type, size_t channelIndex) {
  if (mSignalSource) {
    mSignalSource->setChannelSignalType(channelIndex, type);
  }
}
void MockInputCLI::setSignalSource(std::shared_ptr<SignalSource> signalSource) {
  mSignalSource = signalSource;
}