#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "color.h"
#include "cell.h"

class Snake {
 public:
  enum class Direction { kNone, kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int start_x, int start_y,
  std::vector<std::vector<Cell>>& grid, Color color, bool player_controlled)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(start_x),
        head_y(start_y),
        grid(grid),
        color(color),
        player_controlled(player_controlled) {}

  ~Snake();

  void Update();
  void GrowBody();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  int score{0};
  bool alive{true};
  bool player_controlled{false};
  float head_x;
  float head_y;
  bool ready_for_input{true}; //helps with filtering user input
  std::vector<SDL_Point> body;
  Color color;
  std::vector<std::vector<Cell>>& grid;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void cleanup();

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif