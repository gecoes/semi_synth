#ifndef AUDIORENDERER_H
#define AUDIORENDERER_H

#include "SignalSource.h"
#include "Transport.h"
#include <iostream>
#include <memory>

class AudioRenderer {
public:
  AudioRenderer() = default;
  ~AudioRenderer() = default;

  void renderAudio(float sampleRate);

  void setTransport(std::shared_ptr<Transport> transport);

  void setSignalSource(std::shared_ptr<SignalSource> signalSource);

private:
  std::shared_ptr<Transport> mTransport;
  std::shared_ptr<SignalSource> mSignalSource;
};

#endif // AUDIORENDERER_H