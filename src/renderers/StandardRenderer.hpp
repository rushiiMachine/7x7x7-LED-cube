#pragma once

#include <Arduino.h>
#include "Renderer.hpp"
#include "cube.hpp"

/**
 * Renders the cube with the standard IO utilities provided by Arduino.h
 * This should be the most widely compatible as it does not use any implementation-specific details.
 */
class StandardRenderer : public Renderer {
    byte currentLayer = 0;

public:
    void setup() override {
        // Configure & disable all columns
        for (byte i = 0; i < CUBE_SIZE * CUBE_SIZE; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, LOW);
        }
        // Configure & disable all layers
        for (byte i = 0; i < CUBE_SIZE; i++) {
            pinMode(A0 + i, OUTPUT);
            digitalWrite(A0 + i, LOW);
        }
    }

    void renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) override {
        // Turn off all layers
        for (int l = CUBE_SIZE - 1; l > -1; l--) {
            digitalWrite(A0 + l, LOW);
        }
        // Enable/disable all columns
        for (byte x = 0; x < CUBE_SIZE; x++) {
            for (byte y = 0; y < CUBE_SIZE; y++) {
                digitalWrite(CUBE_SIZE * y + x, model[x][y][currentLayer] ? HIGH : LOW);
            }
        }
        // Turn on current layer
        digitalWrite(A0 + currentLayer, HIGH);
        // Advance layer for next the render
        currentLayer++;
        currentLayer = currentLayer % CUBE_SIZE;
    }
};
