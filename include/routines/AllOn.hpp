#pragma once

#include <Arduino.h>
#include "cube.hpp"
#include "../Routine.hpp"

/**
 * Routine that lights up the entire cube.
 */
class AllOn : public Routine {
public:
    void setup(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) override;
};
