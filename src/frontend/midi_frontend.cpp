// main.cpp
#include "AlsaOutput.h"
#include "MidiInput.h"
#include "RenderEngine.h"
#include "RenderEngineFactory.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {
  auto input = std::make_unique<MidiInput>();
  auto alsaOutput = std::make_shared<AlsaOutput>();

  RenderEngineFactory factory;
  auto renderEngine = factory.createDefault();
  renderEngine->setAudioOutput(alsaOutput);
  renderEngine->start();

  std::cout << "\n== Synth MIDI Ready ==" << std::endl;
  std::cout << "Connecta un teclat MIDI i toca!" << std::endl;
  std::cout << "Prem Ctrl+C per sortir.\n" << std::endl;

  // Bucle principal
  while (!input->shouldExit()) {
    input->processInput(*renderEngine->getAudioRenderer()->getSignalSource());
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  renderEngine->stop();
  std::cout << "Sortint del sintetitzador MIDI." << std::endl;
  return 0;
}