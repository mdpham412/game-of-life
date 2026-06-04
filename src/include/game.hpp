#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE
#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"

class Game {
 private:
  int rows{GameOfLifeConstants::defaultRowCount};
  int cols{GameOfLifeConstants::defaultColCount};
  Color backgroundColour{BLACK};
  Color lineColour{WHITE};
  Color squareColour{WHITE};
  float colourBackground[4]{0.0f, 0.0f, 0.0f, 1.0f};
  float colourLines[4]{1.0f, 1.0f, 1.0f, 1.0f};
  float colourSquares[4]{1.0f, 1.0f, 1.0f, 1.0f};
  std::vector<bool> activated;

  int squareSize;
  int gridWidth;
  int gridHeight;
  int paddingX;
  int paddingY;

 public:
  Game(const int screenWidth, const int screenHeight);
  ~Game();
  void loop();

 private:
  // draws imgui menu
  void options();
  void drawGrid();
  // changes ___Colour variables according to colour____ variables
  void updateColors();
  void draw();
  void checkForSquareActivation();
  void initGridSize();
  int getGridIndex(int row, int col);
  void updateGridSize(int newRows, int newCols);
};
#endif
