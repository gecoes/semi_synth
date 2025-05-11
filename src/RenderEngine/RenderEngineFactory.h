#ifndef RENDER_ENGINE_FACTORY_H
#define RENDER_ENGINE_FACTORY_H

#include "RenderEngine.h"

class RenderEngineFactory {
public:
  RenderEngineFactory();
  ~RenderEngineFactory();
  static std::unique_ptr<RenderEngine> createDefault();
};

#endif // RENDER_ENGINE_FACTORY_H