# CMakeLists.txt per al mòdul de sortida d'àudio (ALSA)

# Crea una biblioteca estàtica o compartida per a la sortida d'àudio
add_library(io_alsa_output
AlsaOutput.cpp
)

add_library(io_lib CLIInput.cpp KeyboardInput.cpp MidiInput.cpp ImageOutputUDP.cpp
)

target_include_directories(io_lib
PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${ALSA_INCLUDE_DIRS}
    ${RTMIDI_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/IO
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
)



target_include_directories(io_alsa_output
PUBLIC
    ${ALSA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/IO
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
)

target_link_libraries(io_alsa_output
PUBLIC
    ${ALSA_LIBRARIES}
)

target_link_libraries(io_lib
PUBLIC
    ${ALSA_LIBRARIES}
    ${SDL2_LIBRARIES}
    rtmidi
    nlohmann_json::nlohmann_json
)



add_subdirectory(test)