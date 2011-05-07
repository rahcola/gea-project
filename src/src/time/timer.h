#ifndef TIME_TIMER_H_
#define TIME_TIMER_H_
#include "clock.h"

namespace Time {

  class ITimer : public IClock {
  public:
    /* Return time elapsed, in milliseconds, since last call to tick().

       Adjust the time returned with speed. See setSpeed().
    */
    virtual double tick() = 0;

    /* Return _now_ as perceived by this clock in milliseconds.
       
       Time returned is altered by speed. See setSpeed().
     */
    virtual double getNow() = 0;

    /* Set parent to a new clock.

       Return false if _parent_ is null.
    */
    virtual bool setParent(IClock *parent) = 0;

    /* Set speed of this clock.

       Valid values are =>0.

       Adjust time shown to observers with speed. If speed is 0.5, time
       returned by tick() is half of the actual time elapsed according
       to parent, and the _now_ returned by getNow() is incremented by
       this value.

       Return false if _speed_ was not valid. In this case speed is not
       altered.
    */
    virtual bool setSpeed(double speed) = 0;
    virtual ~ITimer() {};
  };

  /* Allocate and return a pointer to a new ITimer with _parent_ as it's
     parent.

     Return null if _parent_ was null.
   */
  ITimer *createTimer(IClock *parent);

} //namespace Time
#endif //TIME_TIMER_H_
