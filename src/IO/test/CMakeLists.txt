add_executable(test_auidio_loop
    main.cpp
)

target_link_libraries(test_auidio_loop
    RenderEngine
    SignalSource
    io_alsa_output
)
target_include_directories(test_auidio_loop PRIVATE
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/IO
)

