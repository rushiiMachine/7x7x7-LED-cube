#include "renderers/StandardRenderer.hpp"
#include "wiring.hpp"

void StandardRenderer::setup() {
    // Configure & disable all columns
#ifdef COLUMN_REMAPPING
    for (const auto &row: COLUMN_PIN_MAPPING) {
        for (const auto pin: row) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }
    }
#else
    for (byte i = 0; i < CUBE_SIZE * CUBE_SIZE; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
#endif

    // Configure & disable all layers
#ifdef LAYER_REMAPPING
    for (const auto pin: LAYER_PIN_MAPPING) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
#else
    for (byte i = 0; i < CUBE_SIZE; i++) {
        pinMode(A0 + i, OUTPUT);
        digitalWrite(A0 + i, LOW);
    }
#endif
}

void StandardRenderer::renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    // Turn off previous layer
#ifdef LAYER_REMAPPING
    digitalWrite(LAYER_PIN_MAPPING[currentLayer], LOW);
#else
    digitalWrite(A0 + currentLayer, LOW);
#endif

    // Advance layer for this render
    currentLayer = (currentLayer + 1) % CUBE_SIZE;

    // Enable/disable all columns
    for (byte x = 0; x < CUBE_SIZE; x++) {
        for (byte y = 0; y < CUBE_SIZE; y++) {
#ifdef COLUMN_REMAPPING
            const auto pin = COLUMN_PIN_MAPPING[CUBE_SIZE - 1 - y][x];
#else
            const auto pin = CUBE_SIZE * y + x;
#endif

            digitalWrite(pin, (*model)[x][y][currentLayer]);
        }
    }

    // Turn on current layer
#ifdef LAYER_REMAPPING
    digitalWrite(LAYER_PIN_MAPPING[currentLayer], HIGH);
#else
    digitalWrite(A0 + currentLayer, HIGH);
#endif
}
