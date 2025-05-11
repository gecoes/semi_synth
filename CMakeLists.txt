cmake_minimum_required(VERSION 3.16)
project(SynthProject)

set(CMAKE_CXX_STANDARD 20)
enable_testing()
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)


find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)

add_subdirectory(src/IO)
add_subdirectory(src/RenderEngine)
add_subdirectory(src/SignalSource)
add_subdirectory(src/frontend)