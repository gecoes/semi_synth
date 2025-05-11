#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include "Channel.h"
#include "Mixer.h"
#include "Signal.h"

class ImageRenderer {
public:
  ImageRenderer();
  ~ImageRenderer();

  void renderImage(const std::string &imagePath);
  void stopRendering();
  void setSignalSource(std::shared_ptr<Signal> signalSource);

private:
  std::shared_ptr<Signal> mSignalSource;
};

#endif // IMAGERENDERER_H