#include "OutputSource.h"
#include <alsa/asoundlib.h>
#include <iostream>
#include <vector>

class AlsaOutput : public OutputSource {
public:
  AlsaOutput() : handle(nullptr) {}

  ~AlsaOutput() { stop(); }

  bool initialize() override {
    int err;

    // Configura el dispositiu ALSA (utilitzant una configuració predeterminada)
    if ((err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) <
        0) {
      std::cerr << "Error en obrir el dispositiu ALSA: " << snd_strerror(err)
                << std::endl;
      return false;
    }

    // Configura els paràmetres del dispositiu per 32-bit float
    err = snd_pcm_set_params(handle,
                             SND_PCM_FORMAT_FLOAT_LE, // format de dades: 32-bit
                                                      // float (Little Endian)
                             SND_PCM_ACCESS_RW_INTERLEAVED, // accés intercalat
                             2,     // 2 canals (estèreo)
                             48000, // taxa de mostreig: 48 kHz (o la que sigui)
                             32,    // període de retard (mostres)
                             500000); // Latència (en microsegons)

    if (err < 0) {
      std::cerr << "Error configurant paràmetres ALSA: " << snd_strerror(err)
                << std::endl;
      return false;
    }

    return true;
  }

  void writeBuffer(const float *buffer, size_t size) override {
    int err = snd_pcm_writei(handle, buffer, size);
    if (err < 0) {
      std::cerr << "Error escrivint a ALSA: " << snd_strerror(err) << std::endl;
      snd_pcm_prepare(handle);
    }
  }

  bool isReady() const override { return handle != nullptr; }

  void stop() override {
    if (handle) {
      snd_pcm_close(handle);
      handle = nullptr;
    }
  }

private:
  snd_pcm_t *handle;
};
