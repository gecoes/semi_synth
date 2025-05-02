#ifndef INPUTSOURCE_H
#define INPUTSOURCE_H

#include "SignalSource.h"
#include "Transport.h"
#include <memory>

class InputSource {
public:
  InputSource() = default;
  virtual ~InputSource() = default;

  virtual size_t readFrequency(size_t frequency) = 0;
  virtual size_t readAmplitude(size_t amplitude) = 0;
  virtual size_t readPosX(size_t x) = 0;
  virtual size_t readPosY(size_t y) = 0;
  virtual size_t readSelectedChannel(size_t selectedChannel) = 0;

  virtual void reset() = 0;

private:
  std::shared_ptr<Transport> mTransport;
  std::shared_ptr<SignalSource> mSignalSource;
};

#endif // INPUTSOURCE_H