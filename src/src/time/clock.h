#ifndef TIME_CLOCK_H_
#define TIME_CLOCK_H_

namespace Time {

  class IClock {
  public:
    /* Return now in milliseconds.

       Time is quaranteed to be monotonic.
    */
    virtual double getNow() = 0;
    virtual ~IClock() {};
  };

  /* Allocate and return a pointer to a new IClock */
  IClock *createWallClock();

} //namespace Time
#endif //TIME_CLOCK_H_
