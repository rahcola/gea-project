#include "clock.h"
#include <ctime>
#include <gtest/gtest.h>

namespace {

  void sleep_posix(long ms) {
	struct timespec sleep_time;
	struct timespec rem_time;
	sleep_time.tv_sec = 0;
	sleep_time.tv_nsec = ms * 1000000;
	nanosleep(&sleep_time, &rem_time);
	return;
  }

  TEST(ClockTest, precision) {
	ASSERT_EQ(0, 1);
  }

  TEST(ClockTest, tickLastsAtleastTimeSlept) {
	ASSERT_EQ(0, 1);
  }

} //namespace
