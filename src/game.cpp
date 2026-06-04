#include "game.hpp"

Game::Game(int screenWidth, int screenHeight) {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Game of Life");
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  rlImGuiSetup(true);
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  SetExitKey(KEY_NULL);

  activated.assign(rows * cols, false);
  this->initGridSize();
}
Game::~Game() {
  rlImGuiShutdown();
  CloseWindow();
}
void Game::loop() {
  while (!WindowShouldClose()) {
    this->updateColors();
    this->checkForSquareActivation();
    this->draw();
  }
}
void Game::options() {
  if (ImGui::Begin("Controls")) {
    ImGui::Text("Grid Customization");
    int newRows = rows;
    int newCols = cols;

    bool rows_changed = ImGui::SliderInt("Rows", &newRows, 10, 100);
    bool cols_changed = ImGui::SliderInt("Columns", &newCols, 10, 100);

    if (rows_changed || cols_changed) {
      this->updateGridSize(newRows, newCols);
    }
    ImGui::ColorEdit4("Background Color", (float*)&this->colourBackground);
    ImGui::ColorEdit4("Lines Color", (float*)&this->colourLines);
    ImGui::ColorEdit4("Squares Color", (float*)&this->colourSquares);
    ImGui::Separator();
    ImGui::Text("Simulation Controls");
  }
}
void Game::draw() {
  // frame start
  BeginDrawing();
  ClearBackground(backgroundColour);
  rlImGuiBegin();
  ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

  // frame drawing
  this->drawGrid();
  this->options();

  DrawFPS(0, 0);

  // frame end
  ImGui::End();
  rlImGuiEnd();
  EndDrawing();
}
void Game::updateColors() {
  backgroundColour.r = (unsigned char)(this->colourBackground[0] * 255);
  backgroundColour.g = (unsigned char)(this->colourBackground[1] * 255);
  backgroundColour.b = (unsigned char)(this->colourBackground[2] * 255);
  backgroundColour.a = (unsigned char)(this->colourBackground[3] * 255);
  lineColour.r = (unsigned char)(this->colourLines[0] * 255);
  lineColour.g = (unsigned char)(this->colourLines[1] * 255);
  lineColour.b = (unsigned char)(this->colourLines[2] * 255);
  lineColour.a = (unsigned char)(this->colourLines[3] * 255);
  squareColour.r = (unsigned char)(this->colourSquares[0] * 255);
  squareColour.g = (unsigned char)(this->colourSquares[1] * 255);
  squareColour.b = (unsigned char)(this->colourSquares[2] * 255);
  squareColour.a = (unsigned char)(this->colourSquares[3] * 255);
}
void Game::initGridSize() {
  squareSize = std::min(GetScreenWidth() / cols, GetScreenHeight() / rows) - 1;

  gridWidth = cols * squareSize;
  gridHeight = rows * squareSize;

  paddingX = (GetScreenWidth() - gridWidth) / 2;
  paddingY = (GetScreenHeight() - gridHeight) / 2;
}
void Game::updateGridSize(int newRows, int newCols) {
  std::vector<bool> newActivated(newRows * newCols, false);

  int copyRows = std::min(rows, newRows);
  int copyCols = std::min(cols, newCols);

  for (int row = 0; row < copyRows; row++) {
    for (int col = 0; col < copyCols; col++) {
      newActivated[row * newCols + col] = activated[row * cols + col];
    }
  }

  rows = newRows;
  cols = newCols;
  activated = std::move(newActivated);

  initGridSize();
}
int Game::getGridIndex(int row, int col) { return row * cols + col; }
void Game::drawGrid() {
  // draw activaated squares
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (activated[getGridIndex(row, col)]) {
        DrawRectangle(paddingX + col * squareSize, paddingY + row * squareSize,
                      squareSize, squareSize, squareColour);
      }
    }
  }
  // horizontal lines
  for (int i = 0; i <= rows; i++) {
    DrawLine(paddingX, paddingY + i * squareSize, paddingX + gridWidth,
             paddingY + i * squareSize, lineColour);
  }

  // vertical lines
  for (int i = 0; i <= cols; i++) {
    DrawLine(paddingX + i * squareSize, paddingY, paddingX + i * squareSize,
             paddingY + gridHeight, lineColour);
  }
}
void Game::checkForSquareActivation() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      !ImGui::GetIO().WantCaptureMouse) {
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= paddingX && mousePos.x < paddingX + gridWidth &&
        mousePos.y >= paddingY && mousePos.y < paddingY + gridHeight) {
      int col = (mousePos.x - paddingX) / squareSize;
      int row = (mousePos.y - paddingY) / squareSize;
      int index = getGridIndex(row, col);
      activated[index] = !activated[index];
      std::cout << "toggled square at " << row << " " << col << '\n';
    }
  }
}
