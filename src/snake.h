#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "color.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int start_x, int start_y, Color color, bool player_controlled)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(start_x),
        head_y(start_y),
        color(color),
        player_controlled(player_controlled) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  //checks if the snake is a the right position to eat the food; updates accordingly;
  bool did_eat_food(int x, int y); 

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  int score{0};
  bool alive{true};
  bool player_controlled{false};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  Color color;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif