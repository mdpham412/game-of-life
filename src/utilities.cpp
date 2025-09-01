#include "utilities.hpp"

int squaresInColumn;
int squaresInRow;
std::vector<bool> activated;

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

int getGridIndex(int row, int col) { return row * squaresInRow + col; }

void updateSquare(int row, int col) {
  int count = 0;

  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if (dr == 0 && dc == 0) continue;

      int nr = row + dr;
      int nc = col + dc;

      if (nr >= 0 && nr < squaresInColumn && nc >= 0 && nc < squaresInRow) {
        int idx = getGridIndex(nr, nc);
        if (activated[idx]) count++;
      }
    }
  }

  if (!activated[getGridIndex(row, col)]) {
    if (count == 3) activated[getGridIndex(row, col)] = true;
  } else {
    if (count > 3)
      activated[getGridIndex(row, col)] = false;
    else if (count < 2)
      activated[getGridIndex(row, col)] = false;
  }
}

void updateGrid() {
  for (int row = 0; row < squaresInColumn; row++) {
    for (int col = 0; col < squaresInRow; col++) {
      updateSquare(row, col);
    }
  }
}

void drawGrid() {
  int squareSize = std::min(GetScreenWidth() / squaresInRow,
                            GetScreenHeight() / squaresInColumn) -
                   5;
  int paddingX = (GetScreenWidth() - squaresInColumn * squareSize) / 2;
  int paddingY = (GetScreenHeight() - squaresInRow * squareSize) / 2;

  bool mouseDown{};

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseDown = true;

  for (int row = 0; row < squaresInColumn; row++) {
    for (int col = 0; col < squaresInRow; col++) {
      int index = getGridIndex(row, col);

      int x = paddingX + col * squareSize;
      int y = paddingY + row * squareSize;

      Color curSquareColor = activated[index] ? BLACK : WHITE;

      if (mouseDown &&
          positionInSquare(GetMousePosition(),
                           Vector2(x + squareSize / 2, y + squareSize / 2),
                           squareSize)) {
        activated[index] = !activated[index];
      }

      DrawRectangleLines(x, y, squareSize, squareSize, WHITE);
      DrawRectangle(x, y, squareSize, squareSize, curSquareColor);
    }
  }
}
