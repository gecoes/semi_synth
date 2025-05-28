#ifndef ARDUINO_INPUT_H
#define ARDUINO_INPUT_H

#include "InputSource.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

class ArduinoInput : public InputSource {
public:
  ArduinoInput();
  ~ArduinoInput() override = default;

  void processInput(SignalSource &signalSource) override;

  bool isEditMode() const override { return mEditMode; }
  int getSelectedChannel() const override { return mSelectedChannel; }

private:
  int mSerialFd = -1;
  std::string mSerialBuffer;
  bool mEditMode = false;
  int mSelectedChannel = 0;
  int mSelectedSignal = 0;
  int mSelectedParam = 0;
  SignalSource *mSignalSource;

  void handleMessage(const std::string &line);
};

#endif // ARDUINO_INPUT_H
