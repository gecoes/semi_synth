#include "AudioRenderer.h"
#include "Channel.h"
#include "Mixer.h"
#include "Signal.h"
#include "Transport.h"
#include <array>
#include <fstream>
#include <vector>

int main() {
  auto transport = std::make_shared<Transport>();
  std::array<bool, PULSES> pattern = {
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false, true, false, true, false,
      true, false, true, false, true, false};

  Mixer mixer;
  mixer.setChannelSignalType(0, SignalType::SINE);
  mixer.setChannelFrequency(0, 440);
  mixer.setChannelVolume(0, 1.0f);
  mixer.setChannelPattern(0, pattern);

  AudioRenderer renderer;
  renderer.setTransport(transport);
  renderer.setSignalSource(std::make_shared<Mixer>(mixer));

  constexpr size_t bufferSize = 512;
  float buffer[bufferSize];

  std::ofstream out("test.raw", std::ios::binary);

  // Renderem uns segons
  for (int i = 0; i < 1500; ++i) {
    renderer.renderAudioBuffer(buffer, bufferSize);
    out.write(reinterpret_cast<char *>(buffer), sizeof(float) * bufferSize);
  }

  out.close();
}