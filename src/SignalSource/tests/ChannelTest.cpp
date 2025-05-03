#include "Channel.h"
#include "Signal.h"
#include <array>
#include <gtest/gtest.h>

constexpr float EPSILON = 1e-5;
constexpr float TEST_TIME = 0.01f;
constexpr size_t TEST_FREQUENCY = 440;
constexpr float TEST_VOLUME = 0.8f;

TEST(ChannelTest, DefaultConstructor) {
  Channel channel;
  EXPECT_FLOAT_EQ(channel.getVolume(), 0.0f);
  EXPECT_EQ(channel.getPosX(), 0u);
  EXPECT_EQ(channel.getPosY(), 0u);
}

TEST(ChannelTest, SettersAndGetters) {
  Channel channel;
  channel.setVolume(TEST_VOLUME);
  channel.setPosX(10);
  channel.setPosY(20);

  EXPECT_FLOAT_EQ(channel.getVolume(), TEST_VOLUME);
  EXPECT_EQ(channel.getPosX(), 10u);
  EXPECT_EQ(channel.getPosY(), 20u);
}

TEST(ChannelTest, SetSignalType) {
  Channel channel;

  channel.setSignalType(SignalType::SINE);
  channel.setFrequency(TEST_FREQUENCY);
  EXPECT_NEAR(channel.nextSample(TEST_TIME),
              sin(2.0f * M_PI * TEST_FREQUENCY * TEST_TIME), EPSILON);

  channel.setSignalType(SignalType::SQUARE);
  EXPECT_TRUE(channel.nextSample(TEST_TIME) == 1.0f ||
              channel.nextSample(TEST_TIME) == -1.0f);

  channel.setSignalType(SignalType::SAW);
  EXPECT_NEAR(channel.nextSample(TEST_TIME),
              2.0f * (TEST_TIME * TEST_FREQUENCY -
                      floor(0.5f + TEST_TIME * TEST_FREQUENCY)),
              EPSILON);

  channel.setSignalType(SignalType::SILENCE);
  EXPECT_FLOAT_EQ(channel.nextSample(TEST_TIME), 0.0f);
}

TEST(ChannelTest, SetPattern) {
  Channel channel;
  std::array<bool, PULSES> pattern = {true, false, true, false};
  channel.setPattern(pattern);

  channel.updatePatternStep(false, 0.0f);
  EXPECT_FALSE(pattern[0]);

  channel.updatePatternStep(true, 0.0f);
  EXPECT_TRUE(pattern[0]);
}

TEST(ChannelTest, Reset) {
  Channel channel;
  channel.setVolume(TEST_VOLUME);
  channel.setPosX(10);
  channel.setPosY(20);
  channel.setSignalType(SignalType::SINE);

  channel.reset();

  EXPECT_FLOAT_EQ(channel.getVolume(), 0.0f);
  EXPECT_EQ(channel.getPosX(), 0u);
  EXPECT_EQ(channel.getPosY(), 0u);
  EXPECT_FLOAT_EQ(channel.nextSample(TEST_TIME), 0.0f);
}