#include "timer.h"
#include "gtest/gtest.h"

namespace {

  class TimerTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      wall_ = Time::createWallClock();

      base_ = Time::createTimer(wall_);
      child_ = Time::createTimer(base_);
      other_child_ = Time::createTimer(base_);

      slow_base_ = Time::createTimer(wall_);
      slow_child_ = Time::createTimer(slow_base_);
    }

    virtual void TearDown() {
      delete slow_child_;
      delete other_child_;
      delete child_;
      delete slow_base_;
      delete base_;
      delete wall_;
    }

    Time::IClock *wall_;
    Time::ITimer *slow_base_;
    Time::ITimer *slow_child_;
    Time::ITimer *base_;
    Time::ITimer *child_;
    Time::ITimer *other_child_;
  };

  TEST_F(TimerTest, TimerWithSpeedZeroReturnsZeroOnTick) {
    base_->setSpeed(0.0);
    ASSERT_EQ(0, base_->tick());
  }

  TEST_F(TimerTest, TimerWithNonZeroSpeedReturnsMoreThatZeroOnTick) {
    ASSERT_GT(base_->tick(), 0);
  }

  TEST_F(TimerTest, TimerWithZeroSpeedParentReturnsZeroOnTick) {
    base_->setSpeed(0.0);
    ASSERT_EQ(0, child_->tick());
  }
  
  TEST_F(TimerTest, TimerWithNonZeroSpeedParentReturnsMoreThanZeroOnTick) {
    base_->tick();
    ASSERT_GT(child_->tick(), 0);
  }

  TEST_F(TimerTest, TimerWithParentNotTickedReturnsZeroOnSecondTick) {
    base_->tick();
    child_->tick();
    ASSERT_EQ(0, child_->tick());
  }

  TEST_F(TimerTest, TimersWithSameNonWallClockParentReturnSameOnTick) {
    base_->tick();
    ASSERT_EQ(child_->tick(), other_child_->tick());
  }

  TEST_F(TimerTest, TimersWithSameSpeedAndParentReturnSameOnGetNow) {
    base_->tick();
    ASSERT_EQ(child_->getNow(), other_child_->getNow());
  }

  TEST_F(TimerTest, TimerWithSlowerSpeedReturnsLessOnGetNowThanParent) {
    child_->setSpeed(0.5);
    base_->tick();
    child_->tick();
    ASSERT_LT(child_->getNow(), base_->getNow());
  }

} // namespace
