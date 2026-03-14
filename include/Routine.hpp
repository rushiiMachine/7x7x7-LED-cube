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
     * Whether to use multiple frames during drawing. This
     * should only be enabled when the entire cube is rendered upon
     * every frame @link update@endlink, as opposed to only updating a subset
     * of pixels every update.
     */
    bool useFrameBuffering = false;

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
     * @param cube The current cube state to reconfigure. This contains the previous frame.
     * @param dt Delta time since last frame in microseconds
     */
    virtual void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) {
        // Ignore
    }
};
