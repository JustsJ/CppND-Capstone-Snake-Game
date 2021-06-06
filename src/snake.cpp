#include "snake.h"
#include <cmath>
#include <iostream>


Snake::~Snake(){
  cleanup();
}

void Snake::Update() {

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
    ready_for_input = true;

     //check if the snake dies by running into another snake (or itself)
    if (grid[t_head_x][t_head_y] == Cell::kSnake){
      alive = false;
      //clean up the head
      grid[t_old_x][t_old_y] = Cell::kClear;
    }
    //check if the snake just ate food
    else if (grid[t_head_x][t_head_y] == Cell::kFood){
      growing = true;
      grid[t_head_x][t_head_y] = Cell::kSnake;
      if (player_controlled){
        score++;
      }
    }
    else{
      grid[t_head_x][t_head_y] = Cell::kSnake;
    }
  }
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  grid[prev_head_cell.x][prev_head_cell.y] = Cell::kSnake;

  if (!growing) {
    // Remove the tail from the vector. clears that cell on the grid
    grid[body[0].x][body[0].y] = Cell::kClear;
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  //update grid
  for (SDL_Point const &item: body){
    grid[item.x][item.y] = Cell::kSnake;
  }
}

void Snake::GrowBody() { growing = true; }

//removes the snake entirely from the grid
void Snake::cleanup(){
  for (SDL_Point const &item: body){
    grid[item.x][item.y] = Cell::kClear;
  }
} 