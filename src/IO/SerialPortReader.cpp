#include "SerialPortReader.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstring>
#include <iostream>

SerialPortReader::SerialPortReader(const std::string &devicePath)
{
    mFd = open(devicePath.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (mFd < 0)
    {
        std::cerr << "[Serial] Error obrint " << devicePath << ": " << strerror(errno) << "\n";
        return;
    }
    configurePort();
}

SerialPortReader::~SerialPortReader()
{
    if (mFd >= 0)
    {
        close(mFd);
    }
}

bool SerialPortReader::isOpen() const
{
    return mFd >= 0;
}

bool SerialPortReader::configurePort()
{
    termios tty{};
    if (tcgetattr(mFd, &tty) != 0)
    {
        std::cerr << "[Serial] Error obtenint atributs: " << strerror(errno) << "\n";
        return false;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD); // Activar lectura
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;      // 8 bits
    tty.c_cflag &= ~PARENB;  // Sense paritat
    tty.c_cflag &= ~CSTOPB;  // 1 stop bit
    tty.c_cflag &= ~CRTSCTS; // Sense control de flux

    tty.c_lflag = 0; // Mode "raw"
    tty.c_oflag = 0;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;

    return tcsetattr(mFd, TCSANOW, &tty) == 0;
}

bool SerialPortReader::readLine(std::string &outLine)
{
    if (mFd < 0)
        return false;

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(mFd, &readfds);

    timeval timeout = {0, 1000}; // 1 ms

    int result = select(mFd + 1, &readfds, nullptr, nullptr, &timeout);
    if (result > 0 && FD_ISSET(mFd, &readfds))
    {
        char buf[256];
        ssize_t len = read(mFd, buf, sizeof(buf));
        if (len > 0)
        {
            std::cout << "[Serial] Llegits " << len << " bytes: ";
            for (int i = 0; i < len; ++i)
            {
                unsigned char c = buf[i];
                if (c == '\n')
                    std::cout << "[\\n]";
                else if (c == '\r')
                    std::cout << "[\\r]";
                else if (isprint(c))
                    std::cout << c;
                else
                    std::cout << "[" << std::hex << static_cast<int>(c) << "]";
            }
            std::cout << std::endl;

            mBuffer.append(buf, len);

            // Busca el \n com a delimitador de línia
            auto newline = mBuffer.find('\n');
            if (newline != std::string::npos)
            {
                std::string line = mBuffer.substr(0, newline);
                mBuffer.erase(0, newline + 1);

                // Elimina \r si hi és al final de la línia
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();

                outLine = line;
                std::cout << "[Serial] Línia trobada: " << outLine << std::endl;
                return true;
            }
        }
    }

    return false;
}
