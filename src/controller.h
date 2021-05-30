#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  Controller(Snake& snake);
  void HandleInput(bool &running) const;

 private:
  Snake snake;
  void ChangeDirection(Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif