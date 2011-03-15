#ifndef TIME_TIMER_H_
#define TIME_TIMER_H_
#include "clock.h"

namespace Time {

  class ITimer : public IClock {
  public:
	virtual double tick() = 0;
	virtual double getNow() = 0;
	virtual void setParent(IClock *parent) = 0;
	virtual void setSpeed(double speed) = 0;
	virtual ~ITimer() {};
  };

  ITimer *createTimer();

} //namespace Time
#endif //TIME_TIMER_H_
