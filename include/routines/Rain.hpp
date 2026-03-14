#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"

/**
 * Routine that animates random rain particles falling down.
 */
class Rain : public Routine {
public:
    explicit Rain() {
        this->useFrameBuffering = true;
    }

    void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) override;

private:
    uint32_t spawnDelay = 0;
    uint32_t pixelTimesUs[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE] = {};
    float pixelSpeeds[CUBE_SIZE][CUBE_SIZE] = {};
};
