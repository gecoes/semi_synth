#ifndef ARDUINO_INPUT_H
#define ARDUINO_INPUT_H

#include "InputSource.h"
#include <nlohmann/json.hpp>
#include <memory>
#include <string>

class ArduinoInput : public InputSource
{
public:
    ArduinoInput();
    ~ArduinoInput() override = default;

    void processInput(SignalSource &signalSource) override;

    bool isEditMode() const override { return mEditMode; }
    int getSelectedChannel() const override { return mSelectedChannel; }

private:
    bool mEditMode = false;
    int mSelectedChannel = 0;
    int mSelectedSignal = 0;
    int mSelectedParam = 0;
    SignalSource *mSignalSource;

    void handleMessage(const std::string &line, SignalSource &signalSource);
};

#endif // ARDUINO_INPUT_H
