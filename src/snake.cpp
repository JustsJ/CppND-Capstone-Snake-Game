#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  //std::cout<< "checking if cell is free for body"<<"\n"; //TODO: make a grid for thisvvv
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    //std::cout<< "updating body"<<"\n"; 
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

  //check if the snake dies by running into another snake, updates head in the grid.
  int t_old_x = static_cast<int>(old_x);
  int t_old_y = static_cast<int>(old_y);
  int t_head_x = static_cast<int>(head_x);
  int t_head_y = static_cast<int>(head_y);

  //check if the head has moved, and if the new cell is already occupied
  if ((t_head_x != t_old_x || t_head_y != t_old_y) && grid[t_head_x][t_head_y] == 1){
    alive = false;
    for (auto &item: body){
      grid[static_cast<int>(item.x)][static_cast<int>(item.y)] = 0; 
      grid[t_old_x][t_old_y] = 0;
    }
  }
  else{
    grid[t_old_x][t_old_y] = 0;
    grid[t_head_x][t_head_y] = 1;
  }
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector and the grid
  body.push_back(prev_head_cell);
  grid[static_cast<int>(body.back().x)][static_cast<int>(body.back().y)] = 1;

  if (!growing) {
    // Remove the tail from the vector.
    grid[static_cast<int>(body.front().x)][static_cast<int>(body.front().y)] = 0;
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }
}

void Snake::GrowBody() { growing = true; }

bool Snake::did_eat_food(int x, int y){
  // Check if there's food over here

  int new_x = static_cast<int>(head_x);
  int new_y = static_cast<int>(head_y);

  if (x == new_x && y == new_y) {
    std::cout<<"found food!"<<"\n";
    score++;
    // Grow snake and increase speed.
    GrowBody();
    speed += 0.02;

    return true;
  }
  return false;
}