#include "clock.h"

#ifdef POSIX
#include <time.h>

#elif WINDOWS
#include <Windows.h>
#include <time.h>

#else
#include <ctime>
#endif

namespace Time {

  double now() {
    double millis = 0;

#ifdef POSIX
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    millis = (now.tv_sec * 1000.0) + (now.tv_nsec / 1000000.0);

#elif WINDOWS
    millis = (double)(GetTickCount());

#else
    clock_t now = clock();
    millis = (now / CLOCKS_PER_SEC) * 1000;
#endif

    return millis;
  }

  class Clock : public IClock {
  public:
    double getNow();
  };

  double Clock::getNow() {
    return now();
  }

  IClock *createWallClock() {
    return new Clock;
  }

} //namespace Time
