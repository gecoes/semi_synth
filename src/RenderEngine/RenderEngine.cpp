#include "RenderEngine.h"

RenderEngine::RenderEngine()
    : mAudio(nullptr), mImage(nullptr), mAudioOutput(nullptr),
      mImageOutput(nullptr), mRunning(false) {}

RenderEngine::RenderEngine(std::shared_ptr<AudioRenderer> audio,
                           std::shared_ptr<ImageRenderer> image)
    : mAudio(audio), mImage(image), mAudioOutput(nullptr),
      mImageOutput(nullptr), mRunning(false) {}

void RenderEngine::setAudioOutput(std::shared_ptr<AudioOutput> outputSource) {
  mAudioOutput = outputSource;
  if (mAudioOutput) {
    if (!mAudioOutput->initialize()) {
      throw std::runtime_error("Failed to initialize output source");
    }
  }
}

void RenderEngine::setImageOutput(std::shared_ptr<ImageOutput> imageOutput) {
  mImageOutput = imageOutput;
  if (mImageOutput) {
    if (!mImageOutput->initialize()) {
      throw std::runtime_error("Failed to initialize image output");
    }
  }
}

void RenderEngine::loop() {
  const size_t bufferSize = BUFFER_SIZE;

  while (mRunning) {
    auto start = std::chrono::high_resolution_clock::now();

    mAudio->renderAudioBuffer(mBuffer, bufferSize);

    if (mAudioOutput->isReady()) {
      mAudioOutput->writeBuffer(mBuffer, bufferSize);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double targetDuration = static_cast<double>(bufferSize) / SAMPLE_RATE;
    double delay = targetDuration - elapsed.count();

    if (delay > 0)
      std::this_thread::sleep_for(std::chrono::duration<double>(delay));
  }
}

void RenderEngine::start() {
  mAudioOutput->initialize();
  mRunning = true;
  mThread = std::thread(&RenderEngine::loop, this);
}

void RenderEngine::stop() {
  mRunning = false;
  if (mThread.joinable())
    mThread.join();
}
