#include "sim.h"

void app() {
  char grid[2][SIM_Y_SIZE][SIM_X_SIZE];

  for (int y = 0; y < SIM_Y_SIZE; ++y)
    for (int x = 0; x < SIM_X_SIZE; ++x)
      grid[0][y][x] = simRand() % 2;


  for (char i = 0;; i ^= 1) {
    for (int y = 0; y < SIM_Y_SIZE; ++y)
      for (int x = 0; x < SIM_X_SIZE; ++x)
        simPutPixel(x, y, 0xFF000000 + (grid[i][y][x] ? 0xFFFFFF : 0));
    simFlush();

    for (int y = 0; y < SIM_Y_SIZE; ++y)
      for (int x = 0; x < SIM_X_SIZE; ++x) {
        int neigbours = 0;
        for (int dy = -1; dy < 2; ++dy)
          for (int dx = -1; dx < 2; ++dx) {
            if (dy == 0 && dx == 0) continue;
            neigbours += grid[i][(y + dy + SIM_Y_SIZE) % SIM_Y_SIZE][(x + dx + SIM_X_SIZE) % SIM_X_SIZE];
          }
        if (neigbours == 3) {
          grid[i ^ 1][y][x] = 1;
        } else if (neigbours != 2) {
          grid[i ^ 1][y][x] = 0;
        } else {
          grid[i ^ 1][y][x] = grid[i][y][x];
        }
      }
  }
}
