#include "cpu_controller.h"
#include <iostream>


void CpuController::handle_direction(int food_x, int food_y){

    if (!snake.alive){
        return;
    }

    //see if target direction needs to be reset (if new food was placed)
    if (food_x != target_x || food_y != target_y){
        target_x = food_x;
        target_y = food_y;
        target_direction_y = Snake::Direction::kNone;
        target_direction_x = Snake::Direction::kNone;
    }

    int t_head_x = static_cast<int>(snake.head_x);
    int t_head_y = static_cast<int>(snake.head_y);

    //First, determine the general target direction of the food;

    if (target_direction_x == Snake::Direction::kNone){
        if (food_x - t_head_x > 0){
            target_direction_x = Snake::Direction::kRight;
        }
        else if (food_x - t_head_x < 0){
            target_direction_x = Snake::Direction::kLeft;
        }
    }

    if (target_direction_y == Snake::Direction::kNone){
        if (food_y - t_head_y < 0){
            target_direction_y = Snake::Direction::kUp;
        }
        else if (food_y - t_head_y > 0){
            target_direction_y = Snake::Direction::kDown;
        }
    }

    //determine the axis along which the snake is going
    if (snake.direction == Snake::Direction::kLeft || snake.direction == Snake::Direction::kRight){
        //if an obstacle is in front, try and turn where there isn't any
        if (check_colision(snake.direction,1)){
            
            //if we are at the right place on th y-axis, then avoid in any suitable direction;
            //otherwise, try to move towards target
            Snake::Direction potential_direction = (target_direction_y != Snake::Direction::kNone) ?
                target_direction_y : Snake::Direction::kUp;

            ///try to avoid; if obstacle avoided, reset target direction to be re-evaluated
            if(avoid_obstacle(potential_direction)){
                target_direction_x = Snake::Direction::kNone;
            }

        }

        //no obstacles- check if snake needs to turn more towards the target (without running into anything)
        if (t_head_x == food_x && t_head_y != food_y)
        if(!check_colision(target_direction_y,1)){
            snake.direction = target_direction_y;
        }
        else{
            //something was in the way; need to re-evaluate target direction
            target_direction_x = Snake::Direction::kNone;
        }

    }
    else if (snake.direction == Snake::Direction::kUp || snake.direction == Snake::Direction::kDown){
        //same for the y-axis;
        //if an obstacle is in front, try and turn where there isn't any
        if (check_colision(snake.direction,1)){
            
            //if we are at the right place on th x-axis, then avoid in any suitable direction;
            //otherwise, try to move towards target
            Snake::Direction potential_direction = (target_direction_x != Snake::Direction::kNone) ?
                target_direction_x : Snake::Direction::kLeft;

            ///try to avoid; if obstacle avoided, reset target direction to be re-evaluated
            if(avoid_obstacle(potential_direction)){
                target_direction_y = Snake::Direction::kNone;
            }

        }

        //no obstacles- check if snake needs to turn more towards the target (without running into anything)
        if (t_head_y == food_y && t_head_x != food_x)
        if(!check_colision(target_direction_x,1)){
            snake.direction = target_direction_x;
        }
        else{
            //something was in the way; need to re-evaluate target direction
            target_direction_y= Snake::Direction::kNone;
        }
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
            int y = fmod(i + grid_height, grid_height);
            if (grid[t_head_x][y] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kDown:
        for (int i = t_head_y + 1; i<=t_head_y + range; i++){
            int y = fmod(i + grid_height, grid_height);
            if (grid[t_head_x][y] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kLeft:
        for (int i = t_head_x - 1; i>=t_head_x - range; i--){
            int x = fmod(i + grid_width, grid_width);
            if (grid[x][t_head_y] == 1){
                return true;
            }
        }
        break;
    case Snake::Direction::kRight:
        for (int i = t_head_x + 1; i<=t_head_x + range; i++){
            int x = fmod(i + grid_width, grid_width);
            if (grid[x][t_head_y] == 1){
                return true;
            }
        }
        break;
    }

    return false;
}

Snake::Direction CpuController::get_opposite_direction(Snake::Direction direction){
    switch (direction)
    {
    case Snake::Direction::kRight:
        return Snake::Direction::kLeft;
    case Snake::Direction::kLeft:
        return Snake::Direction::kRight;
    case Snake::Direction::kUp:
        return Snake::Direction::kDown;
    case Snake::Direction::kDown:
        return Snake::Direction::kUp;
    default:
        //should never happen, since none is not really a direction
        return Snake::Direction::kNone;
    }

}

//return true of obstacle in front was just avoided
bool CpuController::avoid_obstacle(Snake::Direction potential_direction){

    //if we can avoid obstacle and turn towards target at the same time, do it
    if (!check_colision(potential_direction,1)){
        snake.direction = potential_direction;
        return true;
    }
    else{
        //nowhere else to go, hope it's not a dead-end
        snake.direction = get_opposite_direction(potential_direction);
        return true;
    }
}
