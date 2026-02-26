#pragma once

#include <Arduino.h>
#include "../Renderer.hpp"
#include "cube.hpp"

/**
 * Renders the cube via interacting with raw port registers.
 *
 * This is specifically designed around the Arduino MEGA Revision 3 (R3) board
 * and may not be compatible with other "MEGA" board variants or revisions.
 *
 * Refer to https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf for a detailed pinout.
 */
class RawRenderer : public Renderer {
    byte currentLayer = 0;

    void setup() override;

    void renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) override;
};
