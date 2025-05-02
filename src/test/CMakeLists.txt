add_executable(test_render_engine
    main.cpp
)

# Enllaça totes les biblioteques del teu projecte
target_link_libraries(test_render_engine
    RenderEngine
    SignalSource
)

target_include_directories(test_render_engine PRIVATE
    ${PROJECT_SOURCE_DIR}/src/RenderEngine
    ${PROJECT_SOURCE_DIR}/src/SignalSource
    ${PROJECT_SOURCE_DIR}/src/IO
)