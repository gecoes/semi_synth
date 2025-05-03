#include "RenderEngine.h"

class RenderEngineFactory {
public:
  RenderEngineFactory();
  ~RenderEngineFactory();
  static std::unique_ptr<RenderEngine> createDefault();
  static std::unique_ptr<RenderEngine>
  createWithOutput(std::unique_ptr<OutputSource> output);
};