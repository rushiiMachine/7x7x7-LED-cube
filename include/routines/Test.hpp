#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"

/**
 * Routine that slowly lights up each pixel one by one, along the x, then y, then z, axis.
 * Once the entire cube is lit up, clear all pixels immediately and restart.
 */
class Test : public Routine {
public:
    void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) override;

private:
    unsigned long elapsedOverflowUs = 0;
    uint16_t litCount = 0;
};
