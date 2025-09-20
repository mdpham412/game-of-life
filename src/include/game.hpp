#ifndef GAME_HPP
#define GAME_HPP
#include <chrono>
#include <cmath>
#include <iostream>

#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "utilities.hpp"

class Game {
 private:
  int rows{40};
  int cols{40};
  int speed{10};
  bool continueWindow = true;
  bool shouldUpdateGrid = false;
  float colorBackground[4]{0.0f, 0.0f, 0.0f, 1.0f};
  float colorLines[4]{1.0f, 1.0f, 1.0f, 1.0f};
  float colorSquares[4]{1.0f, 1.0f, 1.0f, 1.0f};
  std::chrono::steady_clock::time_point begin;

 public:
  Game(const int screenWidth, const int screenHeight);
  ~Game() {
    rlImGuiShutdown();
    CloseWindow();
  }
  void loop();

 private:
  void updateColors();
  void draw();
  void update();
  void options();
};
#endif
