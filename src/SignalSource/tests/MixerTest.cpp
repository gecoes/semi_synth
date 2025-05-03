#include "Mixer.h"
#include "Signal.h"
#include <array>
#include <gtest/gtest.h>
#include <memory>

constexpr float EPSILON = 1e-5;
constexpr float TEST_TIME = 0.01f;
constexpr size_t TEST_FREQUENCY = 440;
constexpr float TEST_VOLUME = 0.5f;

TEST(MixerTest, SetChannelSignalType) {
  Mixer mixer;

  mixer.setChannelSignalType(0, SignalType::SINE);
  mixer.setChannelFrequency(0, TEST_FREQUENCY);
  float expectedSample = sin(2.0f * M_PI * TEST_FREQUENCY * TEST_TIME);
  EXPECT_NEAR(mixer.nextSample(TEST_TIME), expectedSample, EPSILON);

  mixer.setChannelSignalType(0, SignalType::SQUARE);
  float squareSample = mixer.nextSample(TEST_TIME);
  EXPECT_TRUE(squareSample == 1.0f || squareSample == -1.0f);

  mixer.setChannelSignalType(0, SignalType::SAW);
  float sawSample = 2.0f * (TEST_TIME * TEST_FREQUENCY -
                            floor(0.5f + TEST_TIME * TEST_FREQUENCY));
  EXPECT_NEAR(mixer.nextSample(TEST_TIME), sawSample, EPSILON);

  mixer.setChannelSignalType(0, SignalType::SILENCE);
  EXPECT_FLOAT_EQ(mixer.nextSample(TEST_TIME), 0.0f);
}

TEST(MixerTest, SetChannelPattern) {
  Mixer mixer;
  std::array<bool, PULSES> pattern = {true, false, true, false};
  mixer.setChannelPattern(0, pattern);

  mixer.updateChannelPatternStep(0, false, 0.0f);
  EXPECT_FALSE(pattern[0]);

  mixer.updateChannelPatternStep(0, true, 0.0f);
  EXPECT_TRUE(pattern[0]);
}

TEST(MixerTest, SetChannelFrequencyAndVolume) {
  Mixer mixer;

  mixer.setChannelSignalType(0, SignalType::SINE);
  mixer.setChannelFrequency(0, TEST_FREQUENCY);
  mixer.setChannelVolume(0, TEST_VOLUME);

  float expectedSample =
      TEST_VOLUME * sin(2.0f * M_PI * TEST_FREQUENCY * TEST_TIME);
  EXPECT_NEAR(mixer.nextSample(TEST_TIME), expectedSample, EPSILON);
}

TEST(MixerTest, NextSampleMultipleChannels) {
  Mixer mixer;

  mixer.setChannelSignalType(0, SignalType::SINE);
  mixer.setChannelFrequency(0, TEST_FREQUENCY);
  mixer.setChannelVolume(0, TEST_VOLUME);

  mixer.setChannelSignalType(1, SignalType::SQUARE);
  mixer.setChannelFrequency(1, TEST_FREQUENCY);
  mixer.setChannelVolume(1, TEST_VOLUME);

  float sineSample =
      TEST_VOLUME * sin(2.0f * M_PI * TEST_FREQUENCY * TEST_TIME);
  float squareSample =
      TEST_VOLUME * 1.0f; // Square wave alternates between 1 and -1
  float expectedOutput = sineSample + squareSample;

  EXPECT_NEAR(mixer.nextSample(TEST_TIME), expectedOutput, EPSILON);
}