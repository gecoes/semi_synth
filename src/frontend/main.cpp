// main.cpp
#include "AlsaOutput.h"
#include "KeyboardInput.h"
#include "RenderEngine.h"
#include "RenderEngineFactory.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {
  auto input = std::make_unique<KeyboardInput>();
  auto alsaOutput = std::make_shared<AlsaOutput>();

  RenderEngineFactory factory;
  auto renderEngine = factory.createDefault();
  renderEngine->setAudioOutput(alsaOutput);

  renderEngine->start();

  std::cout << "\n== Synth SDL Ready ==" << std::endl;
  std::cout << "[ESC] Exit | [e] Edit mode | [q/w/e/r] Select signal | [0-9] "
               "Channel | Arrows: Freq/Vol"
            << std::endl;

  while (!input->shouldExit()) {
    input->processInput(*renderEngine->getAudioRenderer()->getSignalSource());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  renderEngine->stop();
  std::cout << "SDL Synth exited." << std::endl;
  return 0;
}
