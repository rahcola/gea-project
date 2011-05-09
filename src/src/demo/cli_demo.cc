#include "timer.h"
#include <iostream>
#include <string>
#include <cstdlib>

class Col {
private:
  double count_;
  std::string name_;
public:
  Col(std::string name)
    : count_(0), name_(name) { }
  void on_tick(double time) {
    count_ += time;
    if (count_ > 1000) {
      std::cout << name_ << ": " << time;
      count_ = 0;
    } else {
      std::cout << ".";
    }
  }
};

int main(int argc, char* argv[]) {
  Time::IClock *wall = Time::createWallClock();
  Time::ITimer *world_timer = Time::createTimer(wall);
  Time::ITimer *red_timer = Time::createTimer(world_timer);
  Time::ITimer *green_timer = Time::createTimer(world_timer);
  Time::ITimer *blue_timer = Time::createTimer(world_timer);

  Col red("red");
  Col green("green");
  Col blue("blue");

  if (argc != 4) {
    return 1;
  }

  red_timer->setSpeed(strtod(argv[1],NULL));
  green_timer->setSpeed(strtod(argv[2],NULL));
  blue_timer->setSpeed(strtod(argv[3],NULL));

  double count = 0;
  while (true) {
    count += world_timer->tick();

    if (count > 500) {
      red.on_tick(red_timer->tick());
      std::cout << std::endl;
      green.on_tick(green_timer->tick());
      std::cout << std::endl;
      blue.on_tick(blue_timer->tick());
      std::cout << "\n----\n";
      count = 0;
    }
  }

  return 0;
}
