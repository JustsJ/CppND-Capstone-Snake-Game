#include "snake.h"
#include <vector>

class CpuController{

    public:
    CpuController(Snake& snake, std::vector<std::vector<int>>& grid): snake(snake), grid(grid){};
    void handle_direction(int food_x, int food_y);

    private:
    bool check_colision(Snake::Direction potential_dir, int range);

    Snake& snake;
    std::vector<std::vector<int>>& grid;

};