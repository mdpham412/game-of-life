#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE
#include "constants.hpp"
#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"

class Game {
 private:
  int rows{GameOfLifeConstants::defaultRowCount};
  int cols{GameOfLifeConstants::defaultColCount};
  Color backgroundColour;

 public:
  Game(const int screenWidth, const int screenHeight);
  ~Game();
  void loop();

 private:
  void options();
};
#endif
