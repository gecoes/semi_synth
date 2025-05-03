#ifndef OUTPUTSOURCE_H
#define OUTPUTSOURCE_H
#include <cstddef>

class OutputSource {
public:
  virtual ~OutputSource() = default;

  virtual bool initialize() = 0;

  virtual void writeBuffer(const float *buffer, size_t size) = 0;

  virtual bool isReady() const = 0;

  virtual void stop() = 0;
};

#endif // OUTPUTSOURCE_H