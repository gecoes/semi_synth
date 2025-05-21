cmake_minimum_required(VERSION 3.16)
project(SynthProject)

set(CMAKE_CXX_STANDARD 20)
enable_testing()
include(FetchContent)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(json)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  RtMidi
  GIT_REPOSITORY https://github.com/thestk/rtmidi.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(RtMidi)



find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)

find_package(SDL2 REQUIRED)


add_subdirectory(src/IO)
add_subdirectory(src/RenderEngine)
add_subdirectory(src/SignalSource)
add_subdirectory(src/frontend)