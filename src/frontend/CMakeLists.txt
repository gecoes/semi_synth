set(cli_frontend cli_frontend)
set(midi_frontend midi_frontend)

add_executable(${cli_frontend}
    cli_frontend.cpp
)
add_executable(${midi_frontend} 
    midi_frontend.cpp
)

target_include_directories(${cli_frontend}
PUBLIC
    ${ALSA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/IO
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
)

target_link_libraries(${cli_frontend}
PUBLIC
    ${ALSA_LIBRARIES}
    io_alsa_output
    io_lib
    RenderEngine
    SignalSource

)

target_include_directories(${midi_frontend}
PUBLIC
    ${ALSA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/IO
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
)

target_link_libraries(${midi_frontend}
PUBLIC
    ${ALSA_LIBRARIES}
    io_alsa_output
    io_lib
    RenderEngine
    SignalSource

)

