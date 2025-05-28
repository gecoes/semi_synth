#include "ArduinoInput.h"
#include "SerialPortReader.h"

#include <iostream>
#include <string>

using json = nlohmann::json;

inline const char *toString(SignalType type)
{
    switch (type)
    {
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

ArduinoInput::ArduinoInput()
{
    mEditMode = false;
    mSerial = std::make_unique<SerialPortReader>("/dev/ttyUSB0");
    if (!mSerial->isOpen())
    {
        std::cerr << "[ArduinoInput] No s'ha pogut obrir el port sèrie.\n";
    }
    else
    {
        std::cout << "[ArduinoInput] Serial port initialized.\n";
    }
}

void ArduinoInput::processInput(SignalSource &signalSource)
{
    mSignalSource = &signalSource;

    std::string line;
    while (mSerial && mSerial->readLine(line))
    {
        handleMessage(line);
    }
}

void ArduinoInput::handleMessage(const std::string &line)
{
    if (line.empty())
        return;
    try
    {
        auto j = json::parse(line);
        mEditMode = j["editMode"].get<bool>();
        if (!mEditMode)
        {
            mSignalSource->deactivateChannels();
            return;
        }

        mSelectedChannel = j["channel"].get<int>();
        mSelectedSignal = j["signal"].get<int>();
        mSelectedParam = j["param"].get<int>();
        float value = j["value"].get<float>();
        std::cout << "Editing channel: " << mSelectedChannel + 1
                  << " signal: " << mSelectedSignal << std::endl;

        mSignalSource->deactivateChannels();
        mSignalSource->getChannels()[mSelectedChannel]->activateChannel();

        switch (mSelectedParam)
        {
        case 0:
            mSignalSource->setChannelFrequency(mSelectedChannel, mSelectedSignal, value);
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
            mSignalSource->setChannelSignalType(mSelectedChannel, mSelectedSignal, type);
            std::cout << "Changed signal type to: " << toString(type) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ArduinoInput] Error parsing: " << e.what() << "\n";
        std::cerr << "Offending line: " << line << "\n";
    }
}
