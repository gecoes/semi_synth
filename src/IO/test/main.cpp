#include "AlsaOutput.cpp"
#include "RenderEngineFactory.h"
#include <alsa/asoundlib.h>

void updateFrequency(float frequency, RenderEngine &engine);

int main() {
  AlsaOutput alsaOutput;
  RenderEngineFactory engineFactory;
  auto engine = engineFactory.createDefault();
  engine->setOutputSource(std::make_shared<AlsaOutput>(alsaOutput));
  engine->start();

  std::this_thread::sleep_for(std::chrono::seconds(5));
  updateFrequency(1000.0f, *engine);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  updateFrequency(2000.0f, *engine);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  updateFrequency(500.0f, *engine);
  std::this_thread::sleep_for(std::chrono::seconds(5));

  engine->stop();
  return 0;
}

void updateFrequency(float frequency, RenderEngine &engine) {
  auto mixer = engine.getAudioRenderer()->getSignalSource();
  mixer->setChannelFrequency(0, frequency);
}