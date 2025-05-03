#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "AudioRenderer.h"
#include "ImageRenderer.h"
#include "OutputSource.h"
#include "Transport.h"
#include <atomic>
#include <memory>
#include <thread>

#define BUFFER_SIZE 512

class RenderEngine {
public:
  RenderEngine();
  RenderEngine(std::shared_ptr<AudioRenderer> audio,
               std::shared_ptr<ImageRenderer> image,
               std::shared_ptr<Transport> transport);
  void setOutputSource(std::shared_ptr<OutputSource> outputSource);
  std::shared_ptr<AudioRenderer> getAudioRenderer() { return mAudio; }
  void start();
  void stop();
  void loop();

private:
  std::shared_ptr<AudioRenderer> mAudio;
  std::shared_ptr<ImageRenderer> mImage;
  std::shared_ptr<Transport> mTransport;
  std::shared_ptr<OutputSource> mOutputSource;
  std::atomic<bool> mRunning;
  float mBuffer[BUFFER_SIZE];

  std::thread mThread;
};

#endif // RENDER_ENGINE_H