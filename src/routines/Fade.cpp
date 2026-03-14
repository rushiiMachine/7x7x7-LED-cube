#include "routines/Fade.hpp"
#include "utils.hpp"

constexpr uint32_t STEP_US = 25 * 1000UL; // 25ms
constexpr uint32_t DELAY_MAX_US = 5 * 1000 * 1000UL; // 5s

void Fade::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], const unsigned long dt) {
    if ((delayUs = sat_sub_uint32(delayUs, dt)) > 0) return;
    if ((elapsedOverflowUs += dt) < STEP_US) return;

    elapsedOverflowUs -= STEP_US;

    // Randomly index into the set of pixels that are unchanged
    const auto targetUnchangedIdx = random(unchangedCount);
    auto foundUnchanged = 0;

    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            for (byte z = 0; z < CUBE_SIZE; z++) {
                if (isLighting != (*cube)[x][y][z]) {
                    if (targetUnchangedIdx == foundUnchanged) {
                        (*cube)[x][y][z] = isLighting;
                        unchangedCount--;
                    }
                    foundUnchanged++;
                }
            }
        }
    }

    if (unchangedCount == 0) {
        unchangedCount = PIXELS_COUNT;
        isLighting = !isLighting;

        if (isLighting) {
            delayUs = random(DELAY_MAX_US);
        }
    }
}
