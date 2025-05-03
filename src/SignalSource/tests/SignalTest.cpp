#include "Signal.h"
#include <cmath>
#include <gtest/gtest.h>

constexpr float EPSILON = 1e-5;
constexpr float TEST_FREQUENCY = 440.0f;
constexpr float TEST_AMPLITUDE = 0.5f;
constexpr float TEST_TIME = 0.01f;

TEST(SineWaveTest, SettersAndGetters) {
  SineWave sineWave;
  sineWave.setFrequency(TEST_FREQUENCY);
  sineWave.setAmplitude(TEST_AMPLITUDE);
  EXPECT_FLOAT_EQ(sineWave.getFrequency(), TEST_FREQUENCY);
  EXPECT_FLOAT_EQ(sineWave.getAmplitude(), TEST_AMPLITUDE);
}

TEST(SineWaveTest, NextSample) {
  SineWave sineWave;
  sineWave.setFrequency(TEST_FREQUENCY);
  sineWave.setAmplitude(TEST_AMPLITUDE);

  float expectedSample =
      TEST_AMPLITUDE * sin(2.0f * M_PI * TEST_FREQUENCY * TEST_TIME);
  float actualSample = sineWave.nextSample(TEST_TIME);

  EXPECT_NEAR(actualSample, expectedSample, EPSILON);
}

TEST(SquareWaveTest, SettersAndGetters) {
  SquareWave squareWave;
  squareWave.setFrequency(TEST_FREQUENCY);
  squareWave.setAmplitude(TEST_AMPLITUDE);
  EXPECT_FLOAT_EQ(squareWave.getFrequency(), TEST_FREQUENCY);
  EXPECT_FLOAT_EQ(squareWave.getAmplitude(), TEST_AMPLITUDE);
}

TEST(SquareWaveTest, NextSample) {
  SquareWave squareWave;
  squareWave.setFrequency(TEST_FREQUENCY);
  squareWave.setAmplitude(TEST_AMPLITUDE);

  float actualSample = squareWave.nextSample(TEST_TIME);
  EXPECT_TRUE(actualSample == TEST_AMPLITUDE ||
              actualSample == -TEST_AMPLITUDE);
}

TEST(SawtoothWaveTest, SettersAndGetters) {
  SawtoothWave sawtoothWave;
  sawtoothWave.setFrequency(TEST_FREQUENCY);
  sawtoothWave.setAmplitude(TEST_AMPLITUDE);
  EXPECT_FLOAT_EQ(sawtoothWave.getFrequency(), TEST_FREQUENCY);
  EXPECT_FLOAT_EQ(sawtoothWave.getAmplitude(), TEST_AMPLITUDE);
}

TEST(SawtoothWaveTest, NextSample) {
  SawtoothWave sawtoothWave;
  sawtoothWave.setFrequency(TEST_FREQUENCY);
  sawtoothWave.setAmplitude(TEST_AMPLITUDE);

  float expectedSample =
      TEST_AMPLITUDE * (2.0f * (TEST_TIME * TEST_FREQUENCY -
                                floor(0.5f + TEST_TIME * TEST_FREQUENCY)));
  float actualSample = sawtoothWave.nextSample(TEST_TIME);

  EXPECT_NEAR(actualSample, expectedSample, EPSILON);
}