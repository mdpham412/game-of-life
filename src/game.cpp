#include "game.hpp"
void Game::updateColors() {
  backgroundColor.r = (unsigned char)(this->colorBackground[0] * 255);
  backgroundColor.g = (unsigned char)(this->colorBackground[1] * 255);
  backgroundColor.b = (unsigned char)(this->colorBackground[2] * 255);
  backgroundColor.a = (unsigned char)(this->colorBackground[3] * 255);
  lineColor.r = (unsigned char)(this->colorLines[0] * 255);
  lineColor.g = (unsigned char)(this->colorLines[1] * 255);
  lineColor.b = (unsigned char)(this->colorLines[2] * 255);
  lineColor.a = (unsigned char)(this->colorLines[3] * 255);
  squareColor.r = (unsigned char)(this->colorSquares[0] * 255);
  squareColor.g = (unsigned char)(this->colorSquares[1] * 255);
  squareColor.b = (unsigned char)(this->colorSquares[2] * 255);
  squareColor.a = (unsigned char)(this->colorSquares[3] * 255);
}

Game::Game(int screenWidth, int screenHeight) {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Game of Life");
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  rlImGuiSetup(true);

  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  SetExitKey(KEY_NULL);
  initGrid(cols, rows);
  begin = std::chrono::steady_clock::now();
}

void Game::options() {
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

    ImGui::ColorEdit4("Background Color", (float*)&this->colorBackground);
    ImGui::ColorEdit4("Lines Color", (float*)&this->colorLines);
    ImGui::ColorEdit4("Squares Color", (float*)&this->colorSquares);
  }
}

void Game::draw() {
  BeginDrawing();
  ClearBackground(backgroundColor);
  drawGrid();

  rlImGuiBegin();

  ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

  this->options();
  updateColors();

  DrawFPS(0, 0);

  ImGui::End();
  rlImGuiEnd();
  EndDrawing();
}

void Game::update() {
  namespace sc = std::chrono;

  long long update_interval_us = 1000000 / speed;
  sc::steady_clock::time_point end = sc::steady_clock::now();
  if (!shouldUpdateGrid)
    begin = sc::steady_clock::now();
  else if (sc::duration_cast<sc::microseconds>(end - begin).count() >
           update_interval_us) {
    updateGrid();
    begin = sc::steady_clock::now();
  }
}

void Game::loop() {
  while (!WindowShouldClose() && continueWindow) {
    this->update();
    this->draw();
  }
}
