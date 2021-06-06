#ifndef CPUCONTR_H
#define CPUCONTR_H
#include "snake.h"
#include <vector>

class CpuController{

    public:
    CpuController(Snake& snake, std::vector<std::vector<Cell>>& grid):
     snake(snake), grid(grid),
     grid_width(grid.size()), grid_height(grid[0].size()){};
    void handle_direction(int food_x, int food_y);

    private:
    bool check_colision(Snake::Direction potential_dir, int range);
    Snake::Direction get_opposite_direction(Snake::Direction);
    bool avoid_obstacle(Snake::Direction potential_direction);
    Snake::Direction target_direction_x {Snake::Direction::kNone};
    Snake::Direction target_direction_y {Snake::Direction::kNone};
    int target_x, target_y;
    int grid_width, grid_height;

    Snake& snake;
    std::vector<std::vector<Cell>>& grid;

};

#endif