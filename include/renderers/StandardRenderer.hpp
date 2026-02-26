#pragma once

#include <Arduino.h>
#include "../Renderer.hpp"
#include "cube.hpp"

/**
 * Renders the cube with the standard IO utilities provided by Arduino.h
 * This should be the most widely compatible as it does not use any implementation-specific details.
 */
class StandardRenderer : public Renderer {
    byte currentLayer = 0;

public:
    void setup() override;

    void renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) override;
};
