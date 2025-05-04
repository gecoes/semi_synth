#include "AlsaOutput.cpp"
#include "MockInputCLI.h"
#include "RenderEngineFactory.h"
#include "SignalSource.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void showMenu() {
  std::cout << "\n== Synth CLI ==\n";
  std::cout << "1. List channels\n";
  std::cout << "2. Edit channel\n";
  std::cout << "3. Exit\n";
  std::cout << "Choice: ";
}

void editChannel(MockInputCLI &mockInput, size_t channelIndex) {
  while (true) {
    std::cout << "\n-- Editing Channel --\n";
    std::cout << "1. Change signal type\n";
    std::cout << "2. Frequency\n";
    std::cout << "3. Volume\n";
    std::cout << "4. Panning (posx)\n";
    std::cout << "5. Pattern\n";
    std::cout << "6. Back\n";
    std::cout << "Choice: ";

    int op;
    std::cin >> op;

    if (op == 6)
      break;

    switch (op) {
    case 1: {
      std::cout << "Enter type (sine, square, saw, silence): ";
      std::string type;
      std::cin >> type;
      if (type == "sine") {
        mockInput.updateSignalType(SignalType::SINE, channelIndex);
      } else if (type == "square") {
        mockInput.updateSignalType(SignalType::SQUARE, channelIndex);
      } else if (type == "saw") {
        mockInput.updateSignalType(SignalType::SAW, channelIndex);
      } else if (type == "silence") {
        mockInput.updateSignalType(SignalType::SILENCE, channelIndex);
      } else {
        std::cout << "Unknown signal type.\n";
      }
      break;
    }
    case 2: {
      float freq;
      std::cout << "Frequency: ";
      std::cin >> freq;
      mockInput.updateFrequency(freq, channelIndex);
      break;
    }
    case 3: {
      float vol;
      std::cout << "Volume (0.0 - 1.0): ";
      std::cin >> vol;
      mockInput.updateAmplitude(vol, channelIndex);
      break;
    }
    case 4: {
      float pan;
      std::cout << "Panning (0 left to 1.0 right): ";
      std::cin >> pan;
      mockInput.updatePosX(pan, channelIndex);
      break;
    }
    }
  }
}

int main() {
  auto alsaOutput = std::make_shared<AlsaOutput>();

  RenderEngineFactory engineFactory;
  auto engine = engineFactory.createDefault();
  engine->setOutputSource(alsaOutput);
  std::shared_ptr<SignalSource> mixer =
      engine->getAudioRenderer()->getSignalSource();
  engine->start();

  MockInputCLI mockInput(mixer);
  while (true) {
    showMenu();
    int choice;
    std::cin >> choice;

    if (choice == 3)
      break;

    if (choice == 1) {
      std::cout << "\nChannels:\n";
      for (size_t i = 0; i < mixer->getChannels().size(); ++i) {
        std::cout << i << ": Channel " << i << "\n";
      }
    } else if (choice == 2) {
      int id;
      std::cout << "Channel ID to edit (0, 1, 2, 3): ";
      std::cin >> id;
      if (id >= 0 && id < mixer->getChannels().size()) {
        editChannel(mockInput, id);
      } else {
        std::cout << "Invalid channel ID.\n";
      }
    }
  }
  engine->stop();

  return 0;
}