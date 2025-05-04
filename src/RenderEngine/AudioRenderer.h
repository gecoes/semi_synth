#ifndef AUDIORENDERER_H
#define AUDIORENDERER_H

#include "SignalSource.h"
#include "Transport.h"
#include <iostream>
#include <memory>

class AudioRenderer {
public:
  AudioRenderer();
  AudioRenderer(std::shared_ptr<Transport> transport,
                std::shared_ptr<SignalSource> signalSource);
  ~AudioRenderer() = default;

  void renderAudioBuffer(float *outputBuffer, size_t bufferSize);

  void setTransport(std::shared_ptr<Transport> transport);

  void setSignalSource(std::shared_ptr<SignalSource> signalSource);

  std::shared_ptr<Transport> getTransport() const { return mTransport; }
  std::shared_ptr<SignalSource> getSignalSource() const {
    return mSignalSource;
  }

private:
  std::shared_ptr<Transport> mTransport;
  std::shared_ptr<SignalSource> mSignalSource;
  std::pair<float, float> processSample();
};

#endif // AUDIORENDERER_H