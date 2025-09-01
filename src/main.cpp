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
  initGrid();

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  while (!WindowShouldClose() && continueWindow) {
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
            .count() > 1000000) {
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

    if (ImGui::Begin("Test Window")) {
      ImGui::TextUnformatted("Another window");
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
