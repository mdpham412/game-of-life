#include "raylib.h"
#include "rlImGui.h"

int main() {
  InitWindow(800, 450, "raylib [core] example - basic window");
  rlImGuiSetup(true);

  while (!WindowShouldClose()) {
    BeginDrawing();
    rlImGuiBegin();

    rlImGuiEnd();
    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
