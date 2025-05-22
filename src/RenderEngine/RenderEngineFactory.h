#ifndef RENDER_ENGINE_FACTORY_H
#define RENDER_ENGINE_FACTORY_H

#include "RenderEngine.h"

class RenderEngineFactory
{
public:
  RenderEngineFactory();
  ~RenderEngineFactory();
  static std::unique_ptr<RenderEngine> createDefault();
  static std::unique_ptr<RenderEngine> createMultiSignals();
};

#endif // RENDER_ENGINE_FACTORY_H