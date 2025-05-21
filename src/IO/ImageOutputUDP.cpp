#include "ImageOutputUDP.h"
#include "Channel.h"
#include <cstring>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ImageOutputUDP::ImageOutputUDP(const std::string &ip, int port)
    : mInitialized(false) {
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&mServerAddr, 0, sizeof(mServerAddr));
  mServerAddr.sin_family = AF_INET;
  mServerAddr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &mServerAddr.sin_addr);
}

ImageOutputUDP::~ImageOutputUDP() { stop(); }

bool ImageOutputUDP::initialize() {
  mInitialized = (mSocket >= 0);
  return mInitialized;
}

bool ImageOutputUDP::isReady() const { return mInitialized; }

void ImageOutputUDP::stop() {
  if (mInitialized) {
    close(mSocket);
    mInitialized = false;
  }
}

void ImageOutputUDP::sendState(const SignalSource &source) {
  json json_channels = json::array();

  for (const auto &channel : source.getChannels()) {
    if (channel->isActive()) {
      json json_channel;
      json_channel["x"] = channel->getPosX();
      json_channel["y"] = channel->getPosY();
      json signals = json::array();
      for (int i = 0; i < 4; ++i) {
        json signal;
        signal["amplitude"] = channel->getSignalAmplitude(i);
        signal["frequency"] = channel->getSignalFrequency(i);
        signal["wavetype"] = channel->getSignal(i)->getSignalType();
        signals.push_back(signal);
      }
      json_channel["signals"] = signals;
      json_channels.push_back(json_channel);
    }
  }

  std::string json_str = json_channels.dump();
  sendto(mSocket, json_str.c_str(), json_str.size(), 0,
         (sockaddr *)&mServerAddr, sizeof(mServerAddr));
}
