#include "routines/Fade.hpp"

void Fade::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) {
    if ((elapsedOverflowUs += dt) < FADE_STEP_US) return;
    elapsedOverflowUs -= FADE_STEP_US;

    // Randomly index into the set of pixels that are unchanged
    const auto targetUnchangedIdx = random(unchangedCount);
    auto foundUnchanged = 0;

    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            for (byte z = 0; z < CUBE_SIZE; z++) {
                if (isLighting != *cube[x][y][z]) {
                    if (targetUnchangedIdx == foundUnchanged) {
                        *cube[x][y][z] = isLighting;
                        unchangedCount--;
                    }
                    foundUnchanged++;
                }
            }
        }
    }

    if (unchangedCount == 0) {
        unchangedCount = CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;
        isLighting = !isLighting;
    }
}
