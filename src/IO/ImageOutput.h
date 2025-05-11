// ImageOutput.h
#ifndef IMAGEOUTPUT_H
#define IMAGEOUTPUT_H

#include <cstddef>
#include <vector>

class ImageOutput {
public:
  virtual ~ImageOutput() = default;

  // Initialize connection or resources
  virtual bool initialize() = 0;

  // Send visual data to the output target
  virtual void writeFrame(const std::vector<float> &frameData) = 0;

  // Check if ready to write
  virtual bool isReady() const = 0;

  // Cleanup
  virtual void stop() = 0;
};

#endif // IMAGEOUTPUT_H