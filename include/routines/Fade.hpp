#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"

/**
 * Routine that lights up a random pixel one by one until the entire cube is lit,
 * and then randomly turn them off one by one, and repeat.
 */
class Fade : public Routine {
public:
    void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) override;

private:
    bool isLighting = true;
    uint32_t elapsedOverflowUs = 0;
    uint16_t unchangedCount = PIXELS_COUNT;
};
