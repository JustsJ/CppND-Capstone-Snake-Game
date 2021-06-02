#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "color.h"
#include "snake.h"
#include <vector>




class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int snake_count);
  void Run(Renderer &renderer,
           std::size_t target_frame_duration);
  int GetPlayerScore() const;
  int GetPlayerSize() const;

  //the amount of unoccupied space (width and length wise) given to every snake when the game starts,
  //with the snake itself located roughly in the middle of it.
  constexpr static int space_per_snake = 3;

  //the grid which keeps track of the state of the game. 0-free, 1-snake, 2-food
  std::vector<std::vector<int>> grid;

 private:
  Snake* player_snake;
  std::vector<Snake*> snakes;
  SDL_Point food;
  bool game_over;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update();
};

#endif