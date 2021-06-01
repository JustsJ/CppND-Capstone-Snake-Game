#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int snake_count)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        
        //create all the snakes in the game;
        //Each snake starts with a square of free space around it;
        //each side of that suare is of length SPACE_PER_SNAKE;

        //This puts the snake roughly in the middle of it's square;
        int start_x = SPACE_PER_SNAKE / 2;
        int start_y = SPACE_PER_SNAKE / 2;

        int max_positions_x = grid_width / SPACE_PER_SNAKE;
        int max_pisitions_y = grid_height / SPACE_PER_SNAKE;
        
        for (int i=0;i<snake_count;i++){
          Color color(Colors(i%10));

          //the first snake will always be the player snake, the rest are cpu controlled
          if (i==0){
            
            snakes.push_back(new Snake(grid_width, grid_height,start_x,start_y,color,true));
            player_snake = snakes[0];
            //std::cout<<"player created: "<<snakes[0]<<"\n";
            continue;
          }
          //adjust the start coordinates to make sure each snake has it's space
          if(start_x + SPACE_PER_SNAKE > grid_width){
            start_y += SPACE_PER_SNAKE;
            start_x = SPACE_PER_SNAKE / 2;
          }
          else{
            start_x += SPACE_PER_SNAKE;
          }
          snakes.push_back(new Snake(grid_width, grid_height,start_x,start_y,color,false));
          //std::cout<<"snake created: "<<snakes[i]<<"\n";
        }

  //std::cout<<"creation complete: "<<"\n";
  std::cout<<"player snake: "<<player_snake<<"\n";
  //for (Snake* snake: snakes){
  //  std::cout<<snake<<"\n";
  //}
  PlaceFood();
}

void Game::Run(Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::cout<<"Snake passed to controller: "<<player_snake<<"\n";
  Controller player_controller(*player_snake);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    player_controller.HandleInput(running);
    Update();
    renderer.Render(snakes, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(player_snake->score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  bool cell_is_free;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    cell_is_free = true;
    // Check that the location is not occupied by a snake item before placing
    // food.
    
    for (Snake* snake: snakes){
      cell_is_free &= !snake->SnakeCell(x,y);
    }

    if (cell_is_free) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (game_over) return;

  bool food_eaten = false;

  for (Snake* snake: snakes){
    snake->Update();
    //std::cout<<"taking snake at"<< (&snake)<<"\n";
    //std::cout<<"update 1st snake head_x: "<<std::to_string(snakes[0].head_x)<<"\n";
    //std::cout<<"update 1st snake head_x: "<<std::to_string(snakes[0].head_y)<<"\n";
    food_eaten |= snake->did_eat_food(food.x,food.y);
  }

  if (food_eaten){
    PlaceFood();
  }
}

int Game::GetPlayerScore() const { return player_snake->score; }
int Game::GetPlayerSize() const { return player_snake->size; }