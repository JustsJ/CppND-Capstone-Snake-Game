#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {

  if(!alive){
    cleanup();
    return;
  }

  //reset the flag, this should apply only to the current iteration
  just_ate_food = false;

  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.    
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.


  // Update all of the body vector items if the snake head has moved to a new
  // cell. (and if snake is alive)
  if (alive && (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)) {
    UpdateBody(current_cell, prev_cell);
  }
  else if (!alive){
    cleanup();
  }
}

void Snake::UpdateHead() {
  
  float old_x = head_x;
  float old_y = head_y;

  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);

  
  int t_old_x = static_cast<int>(old_x);
  int t_old_y = static_cast<int>(old_y);
  int t_head_x = static_cast<int>(head_x);
  int t_head_y = static_cast<int>(head_y);

  //checking if the head has moved, and what it ran into, if anything
  if (t_head_x != t_old_x || t_head_y != t_old_y){

    if (player_controlled){
    for (std::vector<int> column: grid){
        for (int cell: column){
          std::cout<<cell<<" ";
        }
        std::cout<<"|\n";
      }
      std::cout<<"------"<<"\n";
    }
     //check if the snake dies by running into another snake (or itself)
    if (grid[t_head_x][t_head_y] == 1){
      alive = false;
      //clean up the head
      grid[t_old_x][t_old_y] = 0;

      std::cout<<"-----rip-----"<<"\n";
    }
    //check if the snake just ate food
    else if (grid[t_head_x][t_head_y] == 2){
      growing = true;
      just_ate_food = true;
      grid[t_head_x][t_head_y] = 1;
    }
    else{
      grid[t_head_x][t_head_y] = 1;
    }
  } 
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  grid[prev_head_cell.x][prev_head_cell.y] = 1;

  if (!growing) {
    // Remove the tail from the vector. clears that cell on the grid
    grid[body[0].x][body[0].y] = 0;
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  //update grid
  for (SDL_Point const &item: body){
    grid[item.x][item.y] = 1;
  }
}

void Snake::GrowBody() { growing = true; }

//removes the snake entirely from the grid
void Snake::cleanup(){
  for (SDL_Point const &item: body){
    grid[item.x][item.y] = 0;
  }
} 