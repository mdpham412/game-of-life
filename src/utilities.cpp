#include "utilities.hpp"

int squaresInColumn;
int squaresInRow;
std::vector<bool> activated;
std::vector<bool> activated_copy;

void initGrid(int col, int row) {
  squaresInColumn = col;
  squaresInRow = row;
  activated = std::vector(squaresInColumn * squaresInRow, false);
}

bool positionInSquare(Vector2 pos, Vector2 squareCenter, int squareSide) {
  if (pos.x >= squareCenter.x - squareSide / 2 &&
      pos.x <= squareCenter.x + squareSide / 2 &&
      pos.y >= squareCenter.y - squareSide / 2 &&
      pos.y <= squareCenter.y + squareSide / 2)
    return true;
  return false;
}

int getGridIndex(int row, int col) { return row * squaresInColumn + col; }

void updateGrid() {
  std::vector<bool> nextActivated = activated;

  for (int row = 0; row < squaresInRow; row++) {
    for (int col = 0; col < squaresInColumn; col++) {
      int count = 0;

      for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
          if (dr == 0 && dc == 0) continue;

          int nr = row + dr;
          int nc = col + dc;

          if (nr >= 0 && nr < squaresInRow && nc >= 0 && nc < squaresInColumn) {
            int idx = getGridIndex(nr, nc);
            if (activated[idx]) count++;
          }
        }
      }

      int current_idx = getGridIndex(row, col);
      if (!activated[current_idx]) {
        if (count == 3) nextActivated[current_idx] = true;
      } else {
        if (count > 3)
          nextActivated[current_idx] = false;
        else if (count < 2)
          nextActivated[current_idx] = false;
      }
    }
  }
  activated = nextActivated;
}

void drawGrid() {
  int squareSize = std::min(GetScreenWidth() / squaresInColumn,
                            GetScreenHeight() / squaresInRow) -
                   1;

  int gridWidth = squaresInColumn * squareSize;
  int gridHeight = squaresInRow * squareSize;
  int paddingX = (GetScreenWidth() - squaresInColumn * squareSize) / 2;
  int paddingY = (GetScreenHeight() - squaresInRow * squareSize) / 2;

  bool mouseDown{};

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= paddingX && mousePos.x < paddingX + gridWidth &&
        mousePos.y >= paddingY && mousePos.y < paddingY + gridHeight) {
      int col = (mousePos.x - paddingX) / squareSize;
      int row = (mousePos.y - paddingY) / squareSize;
      int index = getGridIndex(row, col);
      activated[index] = !activated[index];
    }
  }

  for (int i = 0; i <= squaresInRow; i++) {
    DrawLine(paddingX, paddingY + i * squareSize, paddingX + gridWidth,
             paddingY + i * squareSize, LIGHTGRAY);
  }
  for (int i = 0; i <= squaresInColumn; i++) {
    DrawLine(paddingX + i * squareSize, paddingY, paddingX + i * squareSize,
             paddingY + gridHeight, LIGHTGRAY);
  }

  for (int row = 0; row < squaresInRow; row++) {
    for (int col = 0; col < squaresInColumn; col++) {
      if (activated[getGridIndex(row, col)]) {
        DrawRectangle(paddingX + col * squareSize, paddingY + row * squareSize,
                      squareSize, squareSize, BLACK);
      }
    }
  }
}
