#include "game.hpp"

constexpr int screenWidth{1280};
constexpr int screenHeight{800};

int main(int argc, char* argv[]) {
  Game game(screenWidth, screenHeight);
  game.loop();
  return 0;
}
