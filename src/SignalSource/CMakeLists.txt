add_library(SignalSource
    Signal.cpp
    Channel.cpp
    Mixer.cpp
)

add_subdirectory(tests)

target_include_directories(SignalSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/RenderEngine)