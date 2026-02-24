#pragma once

#include <Arduino.h>
#include "cube.hpp"

/**
 * Standard interface to handle rendering a cube model.
 */
class Renderer {
public:
    virtual ~Renderer() = default;

    /**
     * Configures the pinouts and turns off the entire cube upon initializing this renderer.
     */
    virtual void setup() = 0;

    /**
     * Renders a single layer without blocking. Implementations should keep track of the last rendered layer
     * as multiplexed rendering is progressive, and the cube model may change between layer renders,
     * before a full render of the cube is completed.
     *
     * @param model The current cube model to display.
     */
    virtual void renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) = 0;
};
