#include "AudioRenderer.h"

AudioRenderer::AudioRenderer() : mTransport(nullptr), mSignalSource(nullptr) {}
AudioRenderer::AudioRenderer(std::shared_ptr<Transport> transport,
                             std::shared_ptr<SignalSource> signalSource)
    : mTransport(transport), mSignalSource(signalSource) {}

std::pair<float, float> AudioRenderer::processSample() {
  if (mTransport && mSignalSource) {
    mTransport->advance();
    return mSignalSource->nextSampleStereo(mTransport->getInLoop());
  }
  return std::make_pair(0.0f, 0.0f);
}

void AudioRenderer::renderAudioBuffer(float *outputBuffer, size_t bufferSize) {

  for (size_t i = 0; i < bufferSize; ++i) {
    auto sample = processSample();
    outputBuffer[i * 2] = sample.first;
    outputBuffer[i * 2 + 1] = sample.second;
  }
}

void AudioRenderer::setTransport(std::shared_ptr<Transport> transport) {
  mTransport = transport;
}

void AudioRenderer::setSignalSource(
    std::shared_ptr<SignalSource> signalSource) {
  mSignalSource = signalSource;
}