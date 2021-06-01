#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  Controller(Snake& snake):snake(snake){}
  void HandleInput(bool &running);

 private:
  Snake& snake;
  void ChangeDirection(Snake::Direction input,
                       Snake::Direction opposite);
};

#endif