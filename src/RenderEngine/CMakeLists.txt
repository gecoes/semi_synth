add_library(RenderEngine
    AudioRenderer.cpp
    RenderEngine.cpp
    RenderEngineFactory.cpp
    ImageRenderer.cpp
)

target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/src/SignalSource
${PROJECT_SOURCE_DIR}/src/IO)