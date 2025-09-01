#include <chrono>
#include <cmath>

#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "utilities.hpp"

constexpr int screenWidth = 1280;
constexpr int screenHeight = 800;

float ScaleToDPIF(float value) { return GetWindowScaleDPI().x * value; }
int ScaleToDPII(int value) { return int(GetWindowScaleDPI().x * value); }

int main(int argc, char* argv[]) {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Game of Life");
  SetTargetFPS(144);
  rlImGuiSetup(true);

  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  SetExitKey(KEY_NULL);

  bool continueWindow = true;
  bool shouldUpdateGrid = false;
  int rows = 40;
  int cols = 40;
  int speed = 10;  // updates per second
  initGrid();

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  while (!WindowShouldClose() && continueWindow) {
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    if (IsKeyPressed(KEY_SPACE)) {
      shouldUpdateGrid = !shouldUpdateGrid;
    }

    long long update_interval_us = 1000000 / speed;
    if (std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
            .count() > update_interval_us) {
      begin = std::chrono::steady_clock::now();
      if (shouldUpdateGrid) {
        updateGrid();
      }
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    drawGrid();

    rlImGuiBegin();

    ImGui::DockSpaceOverViewport(0, NULL,
                                 ImGuiDockNodeFlags_PassthruCentralNode);

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
    }

    DrawFPS(0, 0);

    ImGui::End();
    rlImGuiEnd();
    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
