#include "renderers/StandardRenderer.hpp"

void StandardRenderer::setup() {
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

void StandardRenderer::renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    const auto nextLayer = (currentLayer + 1) % CUBE_SIZE;

    // Turn off previous layer
    digitalWrite(A0 + currentLayer, LOW);

    // Enable/disable all columns
    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
            digitalWrite(CUBE_SIZE * y + x, (*model)[x][y][currentLayer]);
        }
    }

    // Turn on current layer
    digitalWrite(A0 + nextLayer, HIGH);

    // Advance layer for the next render
    this->currentLayer = nextLayer;
}
