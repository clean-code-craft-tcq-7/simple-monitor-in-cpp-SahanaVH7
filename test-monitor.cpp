#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}

TEST(Monitor, TemperatureOutOfRange)
{
  std::string msg;

  EXPECT_FALSE(checkVitals(104, 70, 95, msg)); // too high
  EXPECT_EQ(msg, "Temperature is critical!");

  EXPECT_FALSE(checkVitals(94, 70, 95, msg)); // too low
  EXPECT_EQ(msg, "Temperature is critical!");

  EXPECT_TRUE(checkVitals(98.6, 72, 96, msg)); // normal
}
TEST(Monitor, PulseOutOfRange)
{
  std::string msg;

  EXPECT_FALSE(checkVitals(98.6, 50, 95, msg)); // too low
  EXPECT_EQ(msg, "Pulse Rate is out of range!");

  EXPECT_FALSE(checkVitals(98.6, 120, 95, msg)); // too high
  EXPECT_EQ(msg, "Pulse Rate is out of range!");

  EXPECT_TRUE(checkVitals(98.6, 70, 95, msg)); // normal
}

TEST(Monitor, Spo2OutOfRange)
{
  std::string msg;

  EXPECT_FALSE(checkVitals(98.6, 72, 85, msg)); // too low
  EXPECT_EQ(msg, "Oxygen Saturation out of range!");

  EXPECT_TRUE(checkVitals(98.6, 72, 96, msg)); // normal
}

TEST(Monitor, AllVitalsNormal)
{
  std::string msg;

  EXPECT_TRUE(checkVitals(98.6, 72, 96, msg));
  EXPECT_EQ(msg, ""); // no error message when ok
}
