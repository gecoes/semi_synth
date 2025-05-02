add_library(RenderEngine
    AudioRenderer.cpp
    AudioRenderer.h
    Transport.h
    Transport.cpp
)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/src/SignalSource
${PROJECT_SOURCE_DIR}/src/IO)