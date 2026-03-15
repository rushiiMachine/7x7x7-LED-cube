#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"
#include "utils.hpp"

class Snake : public Routine {
public:
    void setup(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) override;

    void update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) override;

private:
    void restart(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]);

    [[nodiscard]]
    Coordinate nextPosition(Direction direction) const;

    bool move(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]);

    bool turnAndMove(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]);

    Coordinate head = {};
    Direction headDirection = {};
    uint32_t elapsedOverflowUs = 0;
};
