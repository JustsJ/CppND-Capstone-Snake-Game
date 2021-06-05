#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake::Direction input,
                                 Snake::Direction opposite) {
  if (snake.direction != opposite || snake.size == 1) {
    snake.direction = input;
  }
  return;
}

void Controller::HandleInput(bool &running) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      //ignore the input unless the snake just moved
      //to prevent the snake from running into itself via quick u-turn
    } else if (e.type == SDL_KEYDOWN && snake.ready_for_input) {
      snake.ready_for_input = false;
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}