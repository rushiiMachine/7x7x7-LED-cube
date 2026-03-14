#pragma once

/**
 * The LED count of the cube along any axis.
 */
#define CUBE_SIZE 7

/**
 * The total amount of LEDs in the cube.
 * For a 7x7x7 cube there is 343 total LEDs.
 */
#define PIXELS_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)

/**
 * The rate to multiplex the entire cube at.
 * This sets the rate at which the entire cube is rendered per second.
 *
 * For example at 60 fps, each layer is lit up for 1/60/CUBE_SIZE of a second, so that
 * all layers are rendered 60 times per second. Generating new frames is done asynchronously,
 * and rendering is non-blocking so that the multiplexing is consistent.
 */
#ifndef REFRESH_RATE
#define REFRESH_RATE 120
#endif
