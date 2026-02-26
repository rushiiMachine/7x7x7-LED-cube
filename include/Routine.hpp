#pragma once

#include <Arduino.h>
#include "cube.hpp"

/**
 * Base routine to configure a custom display for the LED cube.
 */
class Routine {
public:
    virtual ~Routine() = default;

    /**
     * Initially configured the cube display for the first frame of this routine.
     * If this display is static, then the cube can be configured just once here without updating.
     * @param cube The current cube state to reconfigure. This may contain a previous frame from a different routine.
     */
    virtual void setup(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
        // Ignore
    }

    /**
     * Configures the cube display for the next frame.
     * @param dt Delta time since last frame in microseconds
     * @param dt The current cube state to reconfigure. This contains the previous frame.
     */
    virtual void update(unsigned long dt, boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
        // Ignore
    }
};
