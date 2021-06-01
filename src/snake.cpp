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
  //std::cout<<"updating at snake "<<this<<"\n";
  //std::cout<<"pre head_x: "<<std::to_string(head_x)<<"\n";
  //std::cout<<"pre head_y: "<<std::to_string(head_y)<<"\n";

  //std::cout<< "updating head with direction: "; 
  switch (direction) {
    case Direction::kUp:
   //   std::cout<<"up"<<"\n";
      head_y -= speed;
      break;

    case Direction::kDown:
    //  std::cout<<"down"<<"\n";
      head_y += speed;
      break;

    case Direction::kLeft:
     // std::cout<<"left"<<"\n";
      head_x -= speed;
      break;

    case Direction::kRight:
     // std::cout<<"right"<<"\n";
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);

  //std::cout<<"head_x: "<<std::to_string(head_x)<<"\n";
  //std::cout<<"head_y: "<<std::to_string(head_y)<<"\n";
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false; //TODO: move me?
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

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