#include <iostream>
#include <limits>
#include <string>
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

  //TODO ask and verify starting snake amount
  int n;
  std::string s;
  bool run_game = true;
  std::cout << "Welcome to Snake!"<<"\n";

  std::cout << "Please enter the ammount of snakes for this game: ";
    
  bool valid_input;
  do{
    valid_input = true;

    std::cin >> s;
    //check if the input is even a number (doesn't quite work with negative numbers, though)
    for (int i =0;i<s.length();i++){
      if (!std::isdigit(s[i])){
        valid_input = false;
        break;
      }
    }

      //input is a number; check if the ammount is right
    if (valid_input){
      n = std::stoi(s);
      if (n <= 0 || n > 20){
        std::cout <<"\n"<<"Invalid ammount. It should be between 1-20. Try again: ";
        valid_input = false;
      }
    }
      //input not a number- try again
    else{
        std::cout <<"\n"<<"Invalid input. Enter a number between 1-20. Try again: ";
        valid_input = false;
    }
  } while (!valid_input);

  std::cout<< "Starting game with "<<n<<" snakes. Good luck!"<<"\n";

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight,n);
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game over!\n";
  std::cout << "Score: " << game.GetPlayerScore() << "\n";
  std::cout << "Size: " << game.GetPlayerSize() << "\n";
  return 0;
}