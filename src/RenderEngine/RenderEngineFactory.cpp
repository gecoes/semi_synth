#include "RenderEngineFactory.h"
#include "AudioRenderer.h"
#include "ImageRenderer.h"
#include "Mixer.h"
#include "OutputSource.h"
#include "RenderEngine.h"
#include "SignalSource.h"
#include "Transport.h"

RenderEngineFactory::RenderEngineFactory() {}
RenderEngineFactory::~RenderEngineFactory() {}
std::unique_ptr<RenderEngine> RenderEngineFactory::createDefault() {
  auto transport = std::make_shared<Transport>();
  auto mixer = std::make_shared<Mixer>();
  mixer->setChannelSignalType(0, SignalType::SINE);
  mixer->setChannelFrequency(0, 440);
  mixer->setChannelVolume(0, 1.0f);
  auto audioRenderer = std::make_shared<AudioRenderer>();
  audioRenderer->setTransport(transport);
  audioRenderer->setSignalSource(mixer);

  auto imageRenderer = std::make_shared<ImageRenderer>();
  return std::make_unique<RenderEngine>(audioRenderer, imageRenderer,
                                        transport);
}
