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
    ClearBackground(backgroundColour);
    rlImGuiBegin();

    // frame drawing
    this->drawGrid();
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
    bool rows_changed = ImGui::SliderInt("Rows", &rows, 10, 200);
    bool cols_changed = ImGui::SliderInt("Columns", &cols, 10, 200);
    ImGui::Separator();
    ImGui::Text("Simulation Controls");
  }
}
void Game::drawGrid() {
  int squareSize =
      std::min(GetScreenWidth() / cols, GetScreenHeight() / rows) - 1;

  int gridWidth = cols * squareSize;
  int gridHeight = rows * squareSize;

  // space between grid and window border
  int paddingX = (GetScreenWidth() - gridWidth) / 2;
  int paddingY = (GetScreenHeight() - gridHeight) / 2;

  // horizontal lines
  for (int i = 0; i <= rows; i++) {
    DrawLine(paddingX, paddingY + i * squareSize, paddingX + gridWidth,
             paddingY + i * squareSize, lineColor);
  }

  // vertical lines
  for (int i = 0; i <= cols; i++) {
    DrawLine(paddingX + i * squareSize, paddingY, paddingX + i * squareSize,
             paddingY + gridHeight, lineColor);
  }
}
