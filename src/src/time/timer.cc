#include "timer.h"
#include "clock.h"

namespace Time {

  class Timer : public ITimer {
  private:
    IClock *parent_;
    double now_as_to_me_;
    double now_as_to_observer_;
    double speed_;
  public:
    Timer(IClock *parent);
    double tick();
    double getNow();
    void setParent(IClock *parent);
    void setSpeed(double speed);
  };

  Timer::Timer(IClock *parent)
    : parent_(parent),
      now_as_to_me_(parent_->getNow()),
      now_as_to_observer_(now_as_to_me_),
      speed_(1.0) {

  }

  double Timer::tick() {
    double current = parent_->getNow();
    double delta = speed_ * (current - now_as_to_me_);
    now_as_to_me_ = current;
    now_as_to_observer_ += delta;
    return delta;
  }

  double Timer::getNow() {
    return now_as_to_observer_;
  }

  void Timer::setParent(IClock *parent) {
    parent_ = parent;
    now_as_to_me_ = parent_->getNow();
    now_as_to_observer_ = now_as_to_me_;
  }

  void Timer::setSpeed(double speed) {
    if (speed < 0) {
      speed = 0;
    }
    speed_ = speed;
  }

  ITimer *createTimer(IClock *parent) {
    return new Timer(parent);
  }

} //namespace Time
