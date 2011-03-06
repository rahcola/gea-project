#include "timer.h"
#include "clock.h"

namespace Time {

  class Timer : public ITimer {
  private:
	IClock *parent_;
	double now_;
	double speed_;
  public:
	Timer();
	~Timer();
	double tick();
	double getNow();
	void setParent(IClock *parent);
	void setSpeed(double speed);
  };

  Timer::Timer()
	: parent_(createWallClock()),
	  now_(parent_->getNow()),
	  speed_(1.0) {

  }

  Timer::~Timer() {}

  double Timer::tick() {
	double current = parent_->getNow();
	double delta = current - now_;
	now_ = current;
	return speed_ * delta;
  }

  double Timer::getNow() {
	return now_;
  }

  void Timer::setParent(IClock *parent) {
	parent_ = parent;
	now_ = parent_->getNow();
  }

  void Timer::setSpeed(double speed) {
	if (speed < 0) {
	  speed = 0;
	}
	speed_ = speed;
  }

  ITimer *createTimer() {
	return new Timer;
  }

} //namespace Time
