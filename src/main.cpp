#include <chrono>
#include <cmath>
#include <iostream>

#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "utilities.hpp"

constexpr int screenWidth{1280};
constexpr int screenHeight{800};

bool continueWindow = true;
bool shouldUpdateGrid = false;
float colorBackground[4]{0.0f, 0.0f, 0.0f, 1.0f};
float colorLines[4]{1.0f, 1.0f, 1.0f, 1.0f};
float colorSquares[4]{1.0f, 1.0f, 1.0f, 1.0f};
int rows{40};
int cols{40};
int speed{10};

void updateColors() {
  backgroundColor.r = (unsigned char)(colorBackground[0] * 255);
  backgroundColor.g = (unsigned char)(colorBackground[1] * 255);
  backgroundColor.b = (unsigned char)(colorBackground[2] * 255);
  backgroundColor.a = (unsigned char)(colorBackground[3] * 255);
  lineColor.r = (unsigned char)(colorLines[0] * 255);
  lineColor.g = (unsigned char)(colorLines[1] * 255);
  lineColor.b = (unsigned char)(colorLines[2] * 255);
  lineColor.a = (unsigned char)(colorLines[3] * 255);
  squareColor.r = (unsigned char)(colorSquares[0] * 255);
  squareColor.g = (unsigned char)(colorSquares[1] * 255);
  squareColor.b = (unsigned char)(colorSquares[2] * 255);
  squareColor.a = (unsigned char)(colorSquares[3] * 255);
}

int main(int argc, char* argv[]) {
  // Initial setup
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Game of Life");
  SetTargetFPS(144);
  rlImGuiSetup(true);

  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  SetExitKey(KEY_NULL);

  initGrid(cols, rows);

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  // Main loop
  while (!WindowShouldClose() && continueWindow) {
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    // Checks whether its time to update the grid
    long long update_interval_us = 1000000 / speed;
    if (std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
            .count() > update_interval_us) {
      begin = std::chrono::steady_clock::now();
      if (shouldUpdateGrid) {
        updateGrid();
      }
    }

    BeginDrawing();
    ClearBackground(backgroundColor);

    drawGrid();

    rlImGuiBegin();

    ImGui::DockSpaceOverViewport(0, NULL,
                                 ImGuiDockNodeFlags_PassthruCentralNode);

    // ImGui Options Window
    if (ImGui::Begin("Controls")) {
      ImGui::Text("Grid Customization");
      bool rows_changed = ImGui::SliderInt("Rows", &rows, 10, 200);
      bool cols_changed = ImGui::SliderInt("Columns", &cols, 10, 200);
      if (rows_changed || cols_changed) {
        initGrid(cols, rows);
        shouldUpdateGrid = false;
      }

      ImGui::Separator();
      ImGui::Text("Simulation Controls");
      ImGui::SliderInt("Speed (updates/sec)", &speed, 1, 60);

      if (ImGui::Button(shouldUpdateGrid ? "Pause" : "Play")) {
        shouldUpdateGrid = !shouldUpdateGrid;
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset")) {
        initGrid(cols, rows);
        shouldUpdateGrid = false;
      }

      ImGui::ColorEdit4("Background Color", (float*)&colorBackground);
      ImGui::ColorEdit4("Lines Color", (float*)&colorLines);
      ImGui::ColorEdit4("Squares Color", (float*)&colorSquares);
    }

    updateColors();

    DrawFPS(0, 0);

    ImGui::End();
    rlImGuiEnd();
    EndDrawing();
  }

  // Cleanup
  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
