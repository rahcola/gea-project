#include <cstdio>
#include <cstdlib>
#include "timer.h"

class Col {
private:
  double count_;
  char* name_;
public:
  Col(char* name)
  : count_(0), name_(name) { }
  void on_tick(double time) {
	count_ += time;
	if (count_ > 1000) {
	  printf("%s", name_);
	  count_ = 0;
	} else {
	  printf(".");
	}
  }
};

int main(int argc, char *argv[]) {
  Time::IClock *wall = Time::createWallClock();
  Time::ITimer *world_timer = Time::createTimer(wall);
  Time::ITimer *red_timer = Time::createTimer(world_timer);
  Time::ITimer *green_timer = Time::createTimer(world_timer);
  Time::ITimer *blue_timer = Time::createTimer(world_timer);

  if (argc < 4) {
	return 1;
  }

  red_timer->setSpeed(strtod(argv[1], NULL));
  green_timer->setSpeed(strtod(argv[2], NULL));
  blue_timer->setSpeed(strtod(argv[3], NULL));

  Col *red = new Col("red");
  Col *green = new Col("green");
  Col *blue = new Col("blue");

  double count = 0;
  while (true) {
	count += world_timer->tick();
	if (count > 1000) {
	  red->on_tick(red_timer->tick());
	  printf("\t");
	  green->on_tick(green_timer->tick());
	  printf("\t");
	  blue->on_tick(blue_timer->tick());
	  printf("\n");
	  count = 0;
	}
  }

  return 0;
}
