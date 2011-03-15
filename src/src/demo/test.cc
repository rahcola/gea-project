#include "clock.h"
#include "timer.h"
#include <cstdio>
#include <time.h>

int main() {
  Time::ITimer *timer = Time::createTimer();
  struct timespec t = {1, 0};
  struct timespec r;
  timer->tick();
  nanosleep(&t, &r);
  printf("%f\n", timer->tick());
  return 0;
}
