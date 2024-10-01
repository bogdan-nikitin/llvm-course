#include "sim.h"

void app() {
  char grid[2 * SIM_Y_SIZE * SIM_X_SIZE];

  for (int y = 0; y < SIM_Y_SIZE; ++y)
    for (int x = 0; x < SIM_X_SIZE; ++x)
      grid[y * SIM_X_SIZE + x] = simRand() % 2;

  for (char i = 0;; i = !i) {
    for (int y = 0; y < SIM_Y_SIZE; ++y)
      for (int x = 0; x < SIM_X_SIZE; ++x)
        simPutPixel(x, y, 0xFF000000 + (grid[i * SIM_Y_SIZE * SIM_X_SIZE + y * SIM_X_SIZE + x] ? 0xFFFFFF : 0));
    simFlush();

    for (int y = 0; y < SIM_Y_SIZE; ++y) {
      for (int x = 0; x < SIM_X_SIZE; ++x) {
        int neigbours = 0;
        for (int dy = -1; dy < 2; ++dy) {
          for (int dx = -1; dx < 2; ++dx) {
            if (dy == 0 && dx == 0)
              continue;
            int y1 = (y + dy + SIM_Y_SIZE) % SIM_Y_SIZE;
            int x1 = (x + dx + SIM_X_SIZE) % SIM_X_SIZE;
            neigbours += grid[i * SIM_Y_SIZE * SIM_X_SIZE + y1 * SIM_X_SIZE + x1];
          }
        }
        if (neigbours == 3) 
          grid[!i * SIM_Y_SIZE * SIM_X_SIZE + y * SIM_X_SIZE + x] = 1;
        else if (neigbours != 2)
          grid[!i * SIM_Y_SIZE * SIM_X_SIZE + y * SIM_X_SIZE + x] = 0;
        else
          grid[!i * SIM_Y_SIZE * SIM_X_SIZE + y * SIM_X_SIZE + x] = grid[i * SIM_Y_SIZE * SIM_X_SIZE + y * SIM_X_SIZE + x];
      }
    }
  }
}
