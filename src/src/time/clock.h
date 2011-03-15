#ifndef TIME_CLOCK_H_
#define TIME_CLOCK_H_

namespace Time {

  class IClock {
  public:
	virtual double getNow() = 0;
	virtual ~IClock() {};
  };

  IClock *createWallClock();

} //namespace Time
#endif //TIME_CLOCK_H_
