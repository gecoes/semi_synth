cmake_minimum_required(VERSION 3.16)
project(SynthProject)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(src/IO)
add_subdirectory(src/RenderEngine)
add_subdirectory(src/SignalSource)
add_subdirectory(src/test)