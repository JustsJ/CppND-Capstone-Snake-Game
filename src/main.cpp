#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  //TODO ask and verify input, check if the ammount of snakes can fit in the grid, and is >0
  int n;
  std::cout << "Welcome to Snake!"<<"\n";
  std::cout << "Please enter the ammount of snakes for this game: ";
  std::cin >> n;
  while (n <= 0 ){
    std::cout <<"\n"<<"Invalid ammount. It should be atleast 1. Try again: ";
    std:: cin >> n;
  }
  std::cout<< "Starting game with "<<n<<" snakes. Good luck!"<<"\n";

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight,n);
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetPlayerScore() << "\n";
  std::cout << "Size: " << game.GetPlayerSize() << "\n";
  return 0;
}