// AlsaOutput.h
#ifndef ALSAOUTPUT_H
#define ALSAOUTPUT_H

#include "AudioOutput.h"
#include <alsa/asoundlib.h>
#include <cstddef>

class AlsaOutput : public AudioOutput {
public:
  AlsaOutput();
  ~AlsaOutput() override;

  bool initialize() override;
  void writeBuffer(const float *buffer, size_t size) override;
  bool isReady() const override;
  void stop() override;

private:
  snd_pcm_t *handle;
};

#endif // ALSAOUTPUT_H
