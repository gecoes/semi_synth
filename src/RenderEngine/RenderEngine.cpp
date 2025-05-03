#include "RenderEngine.h"

RenderEngine::RenderEngine()
    : mAudio(nullptr), mImage(nullptr), mTransport(nullptr),
      mOutputSource(nullptr), mRunning(false) {}

RenderEngine::RenderEngine(std::shared_ptr<AudioRenderer> audio,
                           std::shared_ptr<ImageRenderer> image,
                           std::shared_ptr<Transport> transport)
    : mAudio(audio), mImage(image), mTransport(transport), mRunning(false) {}

void RenderEngine::setOutputSource(std::shared_ptr<OutputSource> outputSource) {
  mOutputSource = outputSource;
  if (mOutputSource) {
    if (!mOutputSource->initialize()) {
      throw std::runtime_error("Failed to initialize output source");
    }
  }
}

void RenderEngine::loop() {
  const size_t bufferSize = BUFFER_SIZE;

  while (mRunning) {
    auto start = std::chrono::high_resolution_clock::now();

    mAudio->renderAudioBuffer(mBuffer, bufferSize);

    if (mOutputSource->isReady()) {
      mOutputSource->writeBuffer(mBuffer, bufferSize);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double targetDuration =
        static_cast<double>(bufferSize) / mTransport->getSampleRate();
    double delay = targetDuration - elapsed.count();

    if (delay > 0)
      std::this_thread::sleep_for(std::chrono::duration<double>(delay));
  }
}

void RenderEngine::start() {
  mRunning = true;
  mThread = std::thread(&RenderEngine::loop, this);
}

void RenderEngine::stop() {
  mRunning = false;
  if (mThread.joinable())
    mThread.join();
}
