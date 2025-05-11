// SocketImageOutput.h
#ifndef SOCKETIMAGEOUTPUT_H
#define SOCKETIMAGEOUTPUT_H

#include "ImageOutput.h"
#include <netinet/in.h>
#include <string>
#include <vector>

class SocketImageOutput : public ImageOutput {
public:
  SocketImageOutput(int port = 9999);
  ~SocketImageOutput() override;

  bool initialize() override;
  void writeFrame(const std::vector<float> &frameData) override;
  bool isReady() const override;
  void stop() override;

private:
  int mServerSocket;
  int mClientSocket;
  int mPort;
  bool mReady;
  sockaddr_in mServerAddr;
};

#endif // SOCKETIMAGEOUTPUT_H