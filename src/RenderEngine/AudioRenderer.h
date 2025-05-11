#ifndef AUDIORENDERER_H
#define AUDIORENDERER_H

#include "SignalSource.h"
#include <iostream>
#include <memory>

class AudioRenderer {
public:
  AudioRenderer();
  AudioRenderer(std::shared_ptr<SignalSource> signalSource);
  ~AudioRenderer() = default;

  void renderAudioBuffer(float *outputBuffer, size_t bufferSize);

  void setSignalSource(std::shared_ptr<SignalSource> signalSource);

  std::shared_ptr<SignalSource> getSignalSource() const {
    return mSignalSource;
  }

private:
  std::shared_ptr<SignalSource> mSignalSource;
  std::pair<float, float> processSample();
};

#endif // AUDIORENDERER_H