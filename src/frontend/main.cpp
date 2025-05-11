// main.cpp
#include "AlsaOutput.h"
#include "AudioRenderer.h"
#include "InputCLI.h"
#include "RenderEngine.h"
#include "RenderEngineFactory.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {
  auto input = std::make_unique<CLIInput>();
  auto alsaOutput = std::make_shared<AlsaOutput>();

  RenderEngineFactory factory;
  auto renderEngine = factory.createDefault();
  renderEngine->setAudioOutput(alsaOutput);

  renderEngine->start();

  while (true) {
    input->processInput(*renderEngine->getAudioRenderer()->getSignalSource());
  }

  renderEngine->stop();
  return 0;
}
