#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cmath>
#include <vector>

#include "imgui.h"
#include "raylib.h"
#include "raymath.h"

extern Color backgroundColor;
extern Color lineColor;
extern Color squareColor;

void initGrid(int col = 40, int row = 40);
int getGridIndex(int row, int col);
void updateGrid();
void drawGrid();

#endif
