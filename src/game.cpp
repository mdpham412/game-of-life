#include "game.hpp"

Game::Game(int screenWidth, int screenHeight) {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Game of Life");
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  rlImGuiSetup(true);

  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  SetExitKey(KEY_NULL);
}
Game::~Game() {
  rlImGuiShutdown();
  CloseWindow();
}

void Game::loop() {
  while (!WindowShouldClose()) {
    // frame start
    BeginDrawing();
    ClearBackground(BLACK);
    rlImGuiBegin();

    // frame drawing
    DrawText("test", 100, 100, 10, WHITE);
    this->options();

    DrawFPS(0, 0);

    // frame end
    ImGui::End();
    rlImGuiEnd();
    EndDrawing();
  }
}

void Game::options() {
  if (ImGui::Begin("Controls")) {
    ImGui::Text("Grid Customization");
    ImGui::Separator();
    ImGui::Text("Simulation Controls");
  }
}
