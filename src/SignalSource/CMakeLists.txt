add_library(SignalSource
    SignalSource.h
    Signal.h
    Signal.cpp
    Channel.h
    Channel.cpp
    Mixer.h
    Mixer.cpp
)

add_subdirectory(tests)

target_include_directories(SignalSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/RenderEngine)