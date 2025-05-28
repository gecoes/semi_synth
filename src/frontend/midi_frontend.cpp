// main.cpp
#include "AlsaOutput.h"
#include "ArduinoInput.h"
#include "ImageOutputUDP.h"
#include "MidiInput.h"
#include "RenderEngine.h"
#include "RenderEngineFactory.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {
  auto midiInput = std::make_unique<MidiInput>();
  auto arduinoInput = std::make_unique<ArduinoInput>();
  auto alsaOutput = std::make_shared<AlsaOutput>();
  auto imageOutput = std::make_shared<ImageOutputUDP>("127.0.0.1", 12345);

  RenderEngineFactory factory;
  auto renderEngine = factory.createMultiSignals();
  renderEngine->setAudioOutput(alsaOutput);
  renderEngine->setImageOutput(imageOutput);
  renderEngine->start();

  std::cout << "\n== Synth MIDI Ready ==" << std::endl;
  std::cout << "Ctrl+C to exit.\n" << std::endl;

  while (!midiInput->shouldExit()) {
    SignalSource &signalSource =
        *renderEngine->getAudioRenderer()->getSignalSource();
    arduinoInput->processInput(signalSource);

    if (!arduinoInput->isEditMode()) {
      midiInput->processInput(
          *renderEngine->getAudioRenderer()->getSignalSource());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  renderEngine->stop();
  std::cout << "Exiting MIDI synth." << std::endl;
  return 0;
}