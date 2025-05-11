#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "AudioOutput.h"
#include "AudioRenderer.h"
#include "ImageOutput.h"
#include "ImageRenderer.h"
#include <atomic>
#include <memory>
#include <thread>

#define BUFFER_SIZE 1024  // 512 samples per channel
#define SAMPLE_RATE 48000 // 48 kHz

class RenderEngine {
public:
  RenderEngine();
  RenderEngine(std::shared_ptr<AudioRenderer> audio,
               std::shared_ptr<ImageRenderer> imag);
  ~RenderEngine() { stop(); }
  void setAudioRenderer(std::shared_ptr<AudioRenderer> audio) {
    mAudio = audio;
  }
  void setImageRenderer(std::shared_ptr<ImageRenderer> image) {
    mImage = image;
  }
  void setAudioOutput(std::shared_ptr<AudioOutput> audioOutput);
  void setImageOutput(std::shared_ptr<ImageOutput> imageOutut);
  std::shared_ptr<AudioRenderer> getAudioRenderer() { return mAudio; }
  void start();
  void stop();
  void loop();

private:
  std::shared_ptr<AudioRenderer> mAudio;
  std::shared_ptr<ImageRenderer> mImage;
  std::shared_ptr<AudioOutput> mAudioOutput;
  std::shared_ptr<ImageOutput> mImageOutput;
  std::atomic<bool> mRunning;
  float mBuffer[BUFFER_SIZE];

  std::thread mThread;
};

#endif // RENDER_ENGINE_H