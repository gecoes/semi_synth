add_executable(SignalTests main.cpp)

target_link_libraries(SignalTests
  PRIVATE
    GTest::gtest
    GTest::gtest_main
    SignalSource 
)

add_test(NAME SignalTests COMMAND SignalTests)
