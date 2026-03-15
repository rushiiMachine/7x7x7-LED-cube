#include "routines/Test.hpp"

constexpr uint32_t STEP_US = 250 * 1000UL; // 250ms

void Test::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], const unsigned long dt) {
    if ((elapsedOverflowUs += dt) < STEP_US) return;
    elapsedOverflowUs -= STEP_US;

    if (litCount == PIXELS_COUNT) {
        memset(cube, 0, sizeof(*cube));
        litCount = 0;
        return;
    }

    const auto x = litCount % CUBE_SIZE;
    const auto y = litCount / CUBE_SIZE % CUBE_SIZE;
    const auto z = litCount / CUBE_SIZE / CUBE_SIZE;
    (*cube)[x][y][z] = true;

    litCount++;
}
