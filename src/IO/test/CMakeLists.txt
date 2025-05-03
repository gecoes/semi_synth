find_package(GTest REQUIRED)

add_executable(IOTests main.cpp)

target_link_libraries(IOTests
  PRIVATE
    GTest::gtest
    GTest::gtest_main
    RenderEngine
    SignalSource
    io_alsa_output
)

add_test(NAME IOTests COMMAND IOTests)

    

