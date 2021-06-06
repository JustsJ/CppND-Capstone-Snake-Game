# CPPND: Capstone Snake Game (with mutliple snakes)

This is my Capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). It was forked from the example project provided [here](https://github.com/udacity/CppND-Capstone-Snake-Game). 

The main change I made to the project is to allow multiple cpu-controlled snakes to be in the game to compete with the player.

The program starts by asking for the ammount of snakes in the game. 1 is just the player, and anything above will keep adding snakes. Just to be safe, I capped the ammount at 20. The gameplay itself is standard snake- eat food without running into yourself (or others).

The game itself keeps track of all the snakes in a vector. The direction where the snake will go is determined by either the Controller (for player's snake) or the CpuController (for other snakes). The game cycle updates all the snakes one-after-another by calling Snake::Update. Within this method, the Snake will check the cell in the direction given by it's controller, and grow if there is food, or die if there is some obstacle. When a snake dies, it's cleared from memory to keep the game cicle from needlesly processing dead snakes.

The cpu-controlled snake AI is kept in the CpuController class. Each instance of CpuController has a reference to a snake whose direction the controller will be adjusting. All CpuController instances also utilize a common grid object, which is a 2D vector for storing the locations of all snakes. The CpuController tries to advance towards target (food) as much as possible, while avoiding obstacles when needed. When it determines the best course of action, it tells it to the snake object, which will later use this direction when updating itself.

The grid that is used both by Snake and CpuController classes is simply a 2D vector of integers. It's kept in th Game class, and passed to instances of Snake and CpuController by reference, to make sure every object is looking at the same grid. It uses the Cell enum to denote what's in every cell (food, snake, or nothing). 

(Note: due to all the snakes and controllers using the same resource, I was considering a concurent approach, but I couldn't see any improvement with it, since a Snake object would lock the grid for it's entire Update (to keep the head attached to the body), which would be the same as a synchronous apprach.)

The game loop first goes through all the controllers to see where every snake wants to go. After that it updates the state of all snakes by moving them in the direction that was set by each snake's respective controller. If by chance food was eaten, a new piece of food is placed. If a snake dies, it's deleted. After all the adjustments to the state of the game are done, the game renders the result, and if the player is still alive, the loop starts anew.

As for changes in rendering, with multiple snakes came the need for multiple colors, so both Color class and a Colors enum were added. In the game each snake is asigned a color from the enum, so that it's easier to tell them apart.

When the player snake hits an obstacle, the game ends.

## Capstone Rubric points addressed
1. **Loops, Functions, I/O**
  1. **The project demonstrates an understanding of C++ functions and control structures-** examples of control structures used are:
    -*if*, *if..else* and *if..else if..else* (e.g. in snake.cpp lines 62-82),
    -*switch* (e.g. in snake.cpp lines 33-49, cpu_controller.cpp lines 105-141),
    -*while* (e.g. in game.cpp lines 82-118),
    -*do..while* (e.g. in main.cpp lines 25-50),
    -*for* loop (range based and regular)(e.g. in game.cpp lines 71-77, 140-148)
  2. **The project accepts user input and processes the input-** apart from the input used to control the snake (which was already implemented in the example), the program also asks at the start to input the desired ammount of snakes in the game (in main.cpp lines 20-50). If the input is not a number or if the number is not within the desired range (1-20), the program asks the user to try again.
2. **Object Oriented Programming**
  1. **The project uses Object Oriented Programming techniques-** some new classes added to the project are CpuController and Color. Changes to existing classes have also been organized to keep the classes structured (as seen in class definitions in cpu_controller.h, snake.h, game.h).
  2. **Classes use appropriate access specifiers for class members-** self-explanatory, all class members have an explicit access modifier that matches it's intended usage. Seen in .h files like cpu_controller.h, snake.h, game.h.
  3. **Class constructors utilize member initialization lists-** initialization lists are used in classes Game, Snake, CpuController. (seen in game.cpp lines 6-10, snake.h lines 13-21,cpu_controller.h lines 9-12)
  4. **Classes abstract implementation details from their interfaces-** all class, variable and method names are made to give an idea of what it's for. To help with that, there are comments throughout the project explaining how things are working (e.g. all of cpu_controller.cpp, snake.cpp) 
3. **Memory Management**
  1. **The project makes use of references in function declarations-** The grid member of Game class is passed to all the instances of CpuController and Snake by reference, to ensure everyone is looking at the same grid (see constructors for the Snake class in snake.h line 14 and for the CpuController class in cpu_controller.h line 9).
  2. **The project uses destructors appropriately.-** When a Snake dies (i.e. is destroyed, as seen in game.cpp lines 144-147), we need to clear it off of the grid. This is also done in the destructor of the Snake class (snake.cpp lines 6-8). Also, the snake objects are allocated dynamically (game.cpp lines 29 and 45) and also destroyed when the instance of Game class is destroyed (game.cpp lines 51-57), meaning the game is over. 
  3. **The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate-** Similar to the last point, the Game class both allocates instances of Snake and the grid object, and also destroys them when the game is over.

## How to run
Once all the dependencies are met (see below), create a build directory, navigate the terminal there and run the following:

> cmake .. && make

This should create the SnakeGame file in build directory. You can run it via 

> ./SnakeGame

## Dependencies for Running Locally (from [the original example](https://github.com/udacity/CppND-Capstone-Snake-Game))
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

