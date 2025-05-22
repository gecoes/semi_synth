#include "RenderEngineFactory.h"
#include "AudioRenderer.h"
#include "ImageRenderer.h"
#include "Mixer.h"
#include "RenderEngine.h"
#include <cmath>

RenderEngineFactory::RenderEngineFactory() {}
RenderEngineFactory::~RenderEngineFactory() {}
std::unique_ptr<RenderEngine> RenderEngineFactory::createDefault()
{
  auto mixer = std::make_shared<Mixer>();

  int baseMidiNote = 48; // C3
  for (int i = 0; i < 32; ++i)
  {
    float freq = 440.0f * std::pow(2.0f, (baseMidiNote + i - 69) / 12.0f);
    mixer->getChannels()[i]->setSignalFrequency(0, freq);
    mixer->getChannels()[i]->setSignalAmplitude(0, 1.0f);
  }

  auto audioRenderer = std::make_shared<AudioRenderer>(mixer);
  auto renderEngine = std::make_unique<RenderEngine>();
  renderEngine->setAudioRenderer(audioRenderer);
  return renderEngine;
}

std::unique_ptr<RenderEngine> RenderEngineFactory::createMultiSignals()
{
  auto mixer = std::make_shared<Mixer>();

  int baseMidiNote = 48; // C3
  for (int i = 0; i < 32; ++i)
  {
    float freq = 440.0f * std::pow(2.0f, (baseMidiNote + i - 69) / 12.0f);
    mixer->setChannelPosX(i, i + 20);
    mixer->setChannelPosY(i, i + 20);
    mixer->getChannels()[i]->setSignalFrequency(0, freq);
    mixer->getChannels()[i]->setSignalFrequency(1, freq);
    mixer->getChannels()[i]->setSignalFrequency(2, freq);
    mixer->getChannels()[i]->setSignalFrequency(3, freq);
    mixer->getChannels()[i]->setSignalAmplitude(0, 1.0f);
    mixer->setChannelSignalType(i, 0, SignalType::SINE);
    mixer->setChannelSignalType(i, 1, SignalType::SQUARE);
    mixer->getChannels()[i]->setSignalAmplitude(1, 1.0f);
    mixer->getChannels()[i]->setSignalAmplitude(2, 1.0f);
    mixer->getChannels()[i]->setSignalAmplitude(3, 1.0f);
  }

  auto audioRenderer = std::make_shared<AudioRenderer>(mixer);
  auto renderEngine = std::make_unique<RenderEngine>();
  renderEngine->setAudioRenderer(audioRenderer);
  return renderEngine;
}