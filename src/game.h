#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Renderer &renderer,
           std::size_t target_frame_duration);
  int GetPlayerScore() const;
  int GetPlayerSize() const;
  int GetCpuScore() const;
  int GetCpuSize() const;

 private:
  Snake player_snake;
  Snake cpu_snake;
  SDL_Point food;
  private bool game_over;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update();
};

#endif