#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H
#include <cstddef>

class AudioOutput {
public:
  virtual ~AudioOutput() = default;

  virtual bool initialize() = 0;

  virtual void writeBuffer(const float *buffer, size_t size) = 0;

  virtual bool isReady() const = 0;

  virtual void stop() = 0;
};

#endif // AUDIO_OUTPUT_H