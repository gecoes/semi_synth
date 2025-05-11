#include "AudioRenderer.h"

AudioRenderer::AudioRenderer() : mSignalSource(nullptr) {}
AudioRenderer::AudioRenderer(std::shared_ptr<SignalSource> signalSource)
    : mSignalSource(signalSource) {}

std::pair<float, float> AudioRenderer::processSample() {
  if (mSignalSource) {
    return mSignalSource->nextSampleStereo();
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

void AudioRenderer::setSignalSource(
    std::shared_ptr<SignalSource> signalSource) {
  mSignalSource = signalSource;
}