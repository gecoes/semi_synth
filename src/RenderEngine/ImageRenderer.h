#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include "Channel.h"
#include "Mixer.h"
#include "Signal.h"
#include "Transport.h"

class ImageRenderer {
public:
  ImageRenderer();
  ~ImageRenderer();

  void renderImage(const std::string &imagePath);
  void stopRendering();
  void setTransport(std::shared_ptr<Transport> transport);
  void setSignalSource(std::shared_ptr<Signal> signalSource);

private:
  std::shared_ptr<Transport> mTransport;
  std::shared_ptr<Signal> mSignalSource;
};

#endif // IMAGERENDERER_H