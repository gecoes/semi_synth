set(target_name frontend)

add_executable(${target_name}
    main.cpp
)


target_include_directories(${target_name}
PUBLIC
    ${ALSA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/IO
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
)

target_link_libraries(${target_name}
PUBLIC
    ${ALSA_LIBRARIES}
    io_alsa_output
    io_lib
    RenderEngine
    SignalSource

)