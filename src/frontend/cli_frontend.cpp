// main.cpp
#include "AlsaOutput.h"
#include "CLIInput.h" // nou
#include "RenderEngine.h"
#include "RenderEngineFactory.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
// #include "KeyboardInput.h" // comenta això

int main() {
  auto input = std::make_unique<CLIInput>(); // nou
  auto alsaOutput = std::make_shared<AlsaOutput>();

  RenderEngineFactory factory;
  auto renderEngine = factory.createDefault();
  renderEngine->setAudioOutput(alsaOutput);
  renderEngine->start();

  std::cout << "\n== Synth CLI Ready ==" << std::endl;

  while (!input->shouldExit()) {
    input->processInput(*renderEngine->getAudioRenderer()->getSignalSource());
  }

  renderEngine->stop();
  std::cout << "CLI Synth exited." << std::endl;
  return 0;
}