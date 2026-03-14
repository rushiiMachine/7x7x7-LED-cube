#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"

/**
 * Routine that animates a plane ripple going up and down based on trig functions.
 */
class Ripple : public Routine {
public:
    explicit Ripple() {
        this->useFrameBuffering = true;
    }

    void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) override;

private:
    float runtime = 0;
};
