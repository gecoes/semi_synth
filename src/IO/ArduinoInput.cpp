#include "ArduinoInput.h"
#include <fcntl.h>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

using json = nlohmann::json;

inline const char *toString(SignalType type) {
  switch (type) {
  case SignalType::SINE:
    return "sine";
  case SignalType::SQUARE:
    return "square";
  case SignalType::SAW:
    return "saw";
  default:
    return "unknown";
  }
}

ArduinoInput::ArduinoInput() {
  const char *device = "/dev/ttyUSB0";
  mSerialFd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
  if (mSerialFd == -1) {
    perror("[ArduinoInput] Could not open serial port");
    return;
  }

  fcntl(mSerialFd, F_SETFL, 0);

  struct termios options;
  if (tcgetattr(mSerialFd, &options) != 0) {
    perror("[ArduinoInput] Error when configuring serial port");
    close(mSerialFd);
    mSerialFd = -1;
    return;
  }

  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);

  options.c_cflag |= (CLOCAL | CREAD);
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CRTSCTS;

  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_iflag &= ~(IXON | IXOFF | IXANY);
  options.c_oflag &= ~OPOST;

  tcflush(mSerialFd, TCIFLUSH);
  if (tcsetattr(mSerialFd, TCSANOW, &options) != 0) {
    perror("[ArduinoInput] Error aplicant configuració");
    close(mSerialFd);
    mSerialFd = -1;
    return;
  }

  std::cout << "[ArduinoInput] Serial port initialized.\n";
}

void ArduinoInput::processInput(SignalSource &signalSource) {
  mSignalSource = &signalSource;

  if (mSerialFd == -1)
    return;

  char buffer[1];
  while (read(mSerialFd, buffer, 1) == 1) {
    if (buffer[0] == '\n') {
      if (!mSerialBuffer.empty()) {
        handleMessage(mSerialBuffer);
        mSerialBuffer.clear();
      }
    } else {
      mSerialBuffer += buffer[0];
    }
  }
}
void ArduinoInput::handleMessage(const std::string &line) {
  try {
    auto j = json::parse(line);
    mEditMode = j["editMode"].get<bool>();
    if (!mEditMode)
      return;

    mSelectedChannel = j["channel"].get<int>();
    mSelectedSignal = j["signal"].get<int>();
    mSelectedParam = j["param"].get<int>();
    float value = j["value"].get<float>();
    std::cout << "Editing channel: " << mSelectedChannel + 1
              << " signal: " << mSelectedSignal << std::endl;
    mSignalSource->deactivateChannels();
    mSignalSource->getChannels()[mSelectedChannel]->activateChannel();
    switch (mSelectedParam) {
    case 0:
      mSignalSource->setChannelFrequency(mSelectedChannel, mSelectedSignal,
                                         value);
      std::cout << "Changed frequency to: " << value << std::endl;
      break;
    case 1:
      mSignalSource->setChannelVolume(mSelectedChannel, mSelectedSignal, value);
      std::cout << "Changed amplitude to: " << value << std::endl;
      break;
    case 2:
      mSignalSource->setChannelPosX(mSelectedChannel, value);
      std::cout << "Changed channel pos x to: " << value << std::endl;
      break;
    case 3:
      mSignalSource->setChannelPosY(mSelectedChannel, value);
      std::cout << "Changed channel pos y to: " << value << std::endl;
      break;
    case 4:
      SignalType type = static_cast<SignalType>(value);
      mSignalSource->setChannelSignalType(mSelectedChannel, mSelectedSignal,
                                          type);
      std::cout << "Changed signal type to: " << toString(type) << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "[ArduinoInput] Error parsing: " << e.what() << "\n";
    std::cerr << "Offending line: " << line << "\n";
  }
}
