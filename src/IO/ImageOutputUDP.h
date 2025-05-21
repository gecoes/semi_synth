#ifndef IMAGE_OUTPUT_UDP_H
#define IMAGE_OUTPUT_UDP_H

#include "ImageOutput.h"
#include "SignalSource.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class ImageOutputUDP : public ImageOutput {
public:
  ImageOutputUDP(const std::string &ip, int port);
  ~ImageOutputUDP();

  bool initialize() override;
  bool isReady() const override;
  void stop() override;

  void sendState(const SignalSource &source) override;

private:
  int mSocket;
  sockaddr_in mServerAddr;
  bool mInitialized;
};

#endif // IMAGE_OUTPUT_UDP_H
