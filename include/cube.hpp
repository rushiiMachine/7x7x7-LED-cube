#pragma once

/**
 * The LED count of the cube along any axis.
 * 7x7x7 cube = 343 total LEDs
 */
#define CUBE_SIZE 7

/**
 * The rate to multiplex the LEDs at.
 * For example, at 60 fps, each layer is individually turned on and off 60 times per second.
 */
#define REFRESH_RATE 60
