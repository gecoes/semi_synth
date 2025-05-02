#include "AudioRenderer.h"

AudioRenderer::AudioRenderer() : mTransport(nullptr), mSignalSource(nullptr) {}
AudioRenderer::AudioRenderer(std::shared_ptr<Transport> transport,
                             std::shared_ptr<SignalSource> signalSource)
    : mTransport(transport), mSignalSource(signalSource) {}

float AudioRenderer::processSample() {
  if (mTransport && mSignalSource) {
    mTransport->advance();
    return mSignalSource->nextSample(mTransport->getInLoop());
  }
  return 0.0f;
}

void AudioRenderer::renderAudioBuffer(float *outputBuffer, size_t bufferSize) {

  for (size_t i = 0; i < bufferSize; ++i) {
    outputBuffer[i] = processSample();
  }
}

void AudioRenderer::setTransport(std::shared_ptr<Transport> transport) {
  mTransport = transport;
}

void AudioRenderer::setSignalSource(
    std::shared_ptr<SignalSource> signalSource) {
  mSignalSource = signalSource;
}