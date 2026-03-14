#include "routines/Ripple.hpp"

void Ripple::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], const unsigned long dt) {
    runtime += static_cast<float>(dt) / 1500000.0f;

    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            for (int z = 0; z < CUBE_SIZE; ++z) {
                (*cube)[x][y][z] = false;
            }

            const float cDist = sqrt((x - 3) * (x - 3) + (y - 3) * (y - 3));
            const float height = 3 * sin(.75 * cDist + 5 * runtime) + 3;
            const int z = static_cast<int>(height + .5f);

            (*cube)[x][y][z] = true;
        }
    }
}
