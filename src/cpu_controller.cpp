#include "cpu_controller.h"
#include <iostream>


void CpuController::handle_direction(int food_x, int food_y){

    if (!snake.alive){
        return;
    }

    //these will be used to determine the right direction towards food,
    //a negative number means we need to go left (for x-axis) or up(for y-axis),
    //while a positive number points towards right or down. No direction change (for that axis) on 0;
    Snake::Direction direction_x;
    Snake::Direction direction_y;

    int t_head_x = static_cast<int>(snake.head_x);
    int t_head_y = static_cast<int>(snake.head_y);

    if (food_x - t_head_x > 0 && !check_colision(Snake::Direction::kRight, 1)){
        direction_x = Snake::Direction::kRight;
        //std::cout<<"going right \n";
    }
    else if (food_x - t_head_x < 0 && !check_colision(Snake::Direction::kLeft, 1)){
        direction_x = Snake::Direction::kLeft;
        //std::cout<<"going left \n";
    }

    if (food_y - t_head_y < 0 && !check_colision(Snake::Direction::kUp, 1)){
        direction_y = Snake::Direction::kUp;
        //std::cout<<"going up \n";
    }
    else if (food_y - t_head_y > 0 && !check_colision(Snake::Direction::kDown, 1)){
        direction_y = Snake::Direction::kDown;
        //std::cout<<"going down \n";
    }

    
    //if the snake is going in the right direction, then let it keep going;
    if (snake.direction == direction_x || snake.direction == direction_y){
        return;
    }

    switch (snake.direction)
    {
    case Snake::Direction::kUp:
    case Snake::Direction::kDown:
        snake.direction = direction_x;
        break;
    case Snake::Direction::kLeft:
    case Snake::Direction::kRight:
        snake.direction = direction_y;
    default:
        break;
    }
}

//returns true if there is risk of collision
bool CpuController::check_colision(Snake::Direction potential_dir, int range){

    int t_head_x = static_cast<int>(snake.head_x);
    int t_head_y = static_cast<int>(snake.head_y);

    //this will check if for the given direction there is a snake to collide with (within the given range)
    switch (potential_dir){
    case Snake::Direction::kUp:
        for (int i = t_head_y - 1; i>=t_head_y - range; i--){
            if (grid[t_head_x][i] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kDown:
        for (int i = t_head_y + 1; i<=t_head_y + range; i++){
            if (grid[t_head_x][i] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kLeft:
        for (int i = t_head_x - 1; i>=t_head_x - range; i--){
            if (grid[i][t_head_y] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kRight:
        for (int i = t_head_x + 1; i<=t_head_x + range; i++){
            if (grid[i][t_head_y] == 1){
                return true;
            }
        }
        break;
    }

    return false;
}
