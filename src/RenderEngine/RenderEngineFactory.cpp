#include "RenderEngineFactory.h"
#include "AudioRenderer.h"
#include "ImageRenderer.h"
#include "Mixer.h"
#include "RenderEngine.h"
#include <cmath>

RenderEngineFactory::RenderEngineFactory() {}
RenderEngineFactory::~RenderEngineFactory() {}
std::unique_ptr<RenderEngine> RenderEngineFactory::createDefault() {
  auto mixer = std::make_shared<Mixer>();

  int baseMidiNote = 48; // C3
  for (int i = 0; i < 32; ++i) {
    float freq = 440.0f * std::pow(2.0f, (baseMidiNote + i - 69) / 12.0f);
    mixer->getChannels()[i]->setSignalFrequency(0, freq);
    mixer->getChannels()[i]->setSignalAmplitude(0, 1.0f);
  }

  auto audioRenderer = std::make_shared<AudioRenderer>(mixer);
  auto renderEngine = std::make_unique<RenderEngine>();
  renderEngine->setAudioRenderer(audioRenderer);
  return renderEngine;
}
