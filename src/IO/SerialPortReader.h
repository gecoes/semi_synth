#ifndef SERIAL_PORT_READER_H
#define SERIAL_PORT_READER_H

#include <string>
#include <queue>

class SerialPortReader
{
public:
    explicit SerialPortReader(const std::string &devicePath);
    ~SerialPortReader();

    bool isOpen() const;

    // Llegeix dades (no bloquejant). Retorna true si s'ha llegit alguna línia completa.
    bool readLine(std::string &outLine);

private:
    int mFd;
    std::string mBuffer;

    bool configurePort();
};

#endif // SERIAL_PORT_READER_H
