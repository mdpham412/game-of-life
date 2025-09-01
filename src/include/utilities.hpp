#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cmath>
#include <vector>

#include "raylib.h"
#include "raymath.h"

void initGrid(int col = 40, int row = 40);
bool positionInSquare(Vector2 pos, Vector2 squareCenter, int squareSide);
int getGridIndex(int row, int col);
void updateGrid();
void drawGrid();

#endif
