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

inline void AllOn::setup(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            for (byte z = 0; z < CUBE_SIZE; z++) {
                *cube[x][y][z] = true;
            }
        }
    }
}
