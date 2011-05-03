#ifndef TIME_TIMER_H_
#define TIME_TIMER_H_
#include "clock.h"

namespace Time {

  class ITimer : public IClock {
  public:
    /* Return time elapsed since last call to tick().

       Multiply the time returned with speed.
    */
    virtual double tick() = 0;

    /* Return _now_ as perceived by this clock. */
    virtual double getNow() = 0;

    /* Set parent to a new clock. */
    virtual void setParent(IClock *parent) = 0;

    /* Set speed of this clock.

       Valid values are =>0. Adjust time shown to observers with
       speed. So if speed is 0.5, time returned by tick() is half of the
       actual time elapsed, and the _now_ returned by getNow() is
       incremented by this value.
    */
    virtual void setSpeed(double speed) = 0;
    virtual ~ITimer() {};
  };

  ITimer *createTimer(IClock *parent);

} //namespace Time
#endif //TIME_TIMER_H_
