#include "AlsaOutput.h"
#include <alsa/asoundlib.h>
#include <iostream>
#include <thread>

AlsaOutput::AlsaOutput() : handle(nullptr) {}

AlsaOutput::~AlsaOutput() { stop(); }

bool AlsaOutput::initialize()
{
  int err;
  if ((err = snd_pcm_open(&handle, "default",
                          SND_PCM_STREAM_PLAYBACK, 0)) < 0)
  {
    std::cerr << "Error en obrir el dispositiu ALSA: " << snd_strerror(err)
              << std::endl;
    return false;
  }

  err = snd_pcm_set_params(handle, SND_PCM_FORMAT_FLOAT_LE,
                           SND_PCM_ACCESS_RW_INTERLEAVED, 2, 48000, 32, 500000);

  if (err < 0)
  {
    std::cerr << "Error configurant paràmetres ALSA: " << snd_strerror(err)
              << std::endl;
    return false;
  }

  return true;
}
void AlsaOutput::writeBuffer(const float *buffer, size_t size)
{
  while (true)
  {
    snd_pcm_sframes_t framesWritten = snd_pcm_writei(handle, buffer, size);

    if (framesWritten == -EPIPE)
    {
      std::cerr << "ALSA: Underrun detected, preparing..." << std::endl;
      snd_pcm_prepare(handle);
      continue;
    }
    else if (framesWritten == -ESTRPIPE)
    {
      std::cerr << "ALSA: Stream suspended, trying to resume..." << std::endl;
      while ((framesWritten = snd_pcm_resume(handle)) == -EAGAIN)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
      if (framesWritten < 0)
        snd_pcm_prepare(handle);
      continue;
    }
    else if (framesWritten < 0)
    {
      std::cerr << "ALSA: Write error: " << snd_strerror(framesWritten)
                << std::endl;
      snd_pcm_prepare(handle);
      continue;
    }
    else if (framesWritten < (snd_pcm_sframes_t)size)
    {
      std::cerr << "ALSA: Partial write: " << framesWritten << " / " << size
                << std::endl;
    }

    break; // write successful
  }
}

bool AlsaOutput::isReady() const { return handle != nullptr; }

void AlsaOutput::stop()
{
  if (handle)
  {
    snd_pcm_close(handle);
    handle = nullptr;
  }
}
