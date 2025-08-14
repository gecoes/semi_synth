#include "RenderEngine.h"

RenderEngine::RenderEngine()
    : mAudio(nullptr), mImage(nullptr), mAudioOutput(nullptr),
      mImageOutput(nullptr), mRunning(false) {}

RenderEngine::RenderEngine(std::shared_ptr<AudioRenderer> audio,
                           std::shared_ptr<ImageRenderer> image)
    : mAudio(audio), mImage(image), mAudioOutput(nullptr),
      mImageOutput(nullptr), mRunning(false) {}

void RenderEngine::setAudioOutput(std::shared_ptr<AudioOutput> outputSource)
{
  mAudioOutput = outputSource;
  if (mAudioOutput)
  {
    if (!mAudioOutput->initialize())
    {
      throw std::runtime_error("Failed to initialize output source");
    }
  }
}

void RenderEngine::setImageOutput(std::shared_ptr<ImageOutput> imageOutput)
{
  mImageOutput = imageOutput;
  if (mImageOutput)
  {
    if (!mImageOutput->initialize())
    {
      throw std::runtime_error("Failed to initialize image output");
    }
  }
}

void RenderEngine::loop()
{
  const unsigned channels = 2;
  const size_t samples_per_chunk = BUFFER_SIZE; // p. ex. 1024 mostres (512 frames estèreo)
  const size_t frames_per_chunk = samples_per_chunk / channels;

  while (mRunning)
  {
    auto start = std::chrono::high_resolution_clock::now();

    mAudio->renderAudioBuffer(mBuffer, samples_per_chunk);
    if (mAudioOutput && mAudioOutput->isReady())
    {
      // writeBuffer accepta "mostres" i ell ja converteix a frames
      mAudioOutput->writeBuffer(mBuffer, samples_per_chunk);
    }

    if (mImageOutput && mImageOutput->isReady())
    {
      mImageOutput->sendState(*mAudio->getSignalSource());
    }

    // (Opcional) un petit yield per no monopolitzar la CPU si tot va molt sobrat:
    // std::this_thread::yield();
    // Evita dormir si pot fer-te arribar tard a l'escriptura següent.
  }
}

void RenderEngine::start()
{
  mAudioOutput->initialize();
  mRunning = true;
  mThread = std::thread(&RenderEngine::loop, this);
}

void RenderEngine::stop()
{
  mRunning = false;
  if (mThread.joinable())
    mThread.join();
}
