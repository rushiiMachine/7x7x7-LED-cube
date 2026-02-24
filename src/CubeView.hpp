#pragma once

#include <Arduino.h>
#include "cube.hpp"

/**
 * Handles setting up and rendering each cube frame.
 */
class CubeView {
public:
    CubeView();

    void displayLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]);

private:
    byte currentLayer;
};

// TODO: write directly to registers and bypass digitalWrite/pinMode

inline CubeView::CubeView() {
    currentLayer = 0;
    for (byte i = 0; i < CUBE_SIZE * CUBE_SIZE; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    for (byte i = 0; i < CUBE_SIZE; i++) {
        pinMode(A0 + i, OUTPUT);
        digitalWrite(A0 + i, LOW);
    }
}

inline void CubeView::displayLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    for (int l = CUBE_SIZE - 1; l > -1; l--) {
        digitalWrite(A0 + l, LOW);
    }
    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            if (model[x][y][currentLayer]) {
                digitalWrite(CUBE_SIZE * y + x, HIGH);
            } else {
                digitalWrite(CUBE_SIZE * y + x, LOW);
            }
        }
    }
    digitalWrite(A0 + currentLayer, HIGH);
    currentLayer++;
    currentLayer = currentLayer % CUBE_SIZE;
}
