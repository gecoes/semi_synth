#include "ArduinoInput.h"
#include <iostream>
#include <string>

using json = nlohmann::json;

ArduinoInput::ArduinoInput()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
}

void ArduinoInput::processInput()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (!line.empty())
        {
            handleMessage(line, mSignalSource);
        }
    }
}

void ArduinoInput::handleMessage(const std::string &line, SignalSource &signalSource)
{
    try
    {
        auto j = json::parse(line);
        mEditMode = j["editMode"].get<bool>();
        if (!mEditMode)
            return;

        mSelectedChannel = j["channel"].get<int>();
        mSelectedSignal = j["signal"].get<int>();
        mSelectedParam = j["param"].get<int>();
        float value = j["value"].get<float>();
        std::cout << "Editing channel: " << mSelectedChannel + 1 << " signal: " << mSelectedSignal << std::endl;
        switch (mSelectedParam)
        {
        case 0:
            signalSource.setChannelFrequency(mSelectedChannel, mSelectedSignal, value);
            std::cout << "Changed frequency to: " << value << std::endl;
            break;
        case 1:
            signalSource.setChannelVolume(mSelectedChannel, mSelectedSignal, value);
            std::cout << "Changed amplitude to: " << value << std::endl;
            break;
        case 2:
            signalSource.setChannelPosX(mSelectedChannel, value);
            std::cout << "Changed channel pos x to: " << value << std::endl;
            break;
        case 3:
            signalSource.setChannelPosY(mSelectedChannel, value);
            std::cout << "Changed channel pos y to: " << value << std::endl;
            break;
        case 4:
            SignalType type = static_cast<SignalType>(value);
            signalSource.setChannelSignalType(mSelectedChannel, mSelectedSignal, type);
            std::cout << "Changed signal type to: " << toString(type) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ArduinoInput] Error parsing: " << e.what() << "\n";
        std::cerr << "Offending line: " << line << "\n";
    }
}

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
