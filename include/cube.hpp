#pragma once

/**
 * The LED count of the cube along any axis.
 * For a 7x7x7 cube there is 343 total LEDs.
 */
#define CUBE_SIZE 7

/**
 * The rate to multiplex the LEDs at.
 * For example, at 60 fps, each layer is individually turned on and off 60 times per second.
 * TODO: verify this claim
 */
#define REFRESH_RATE 60

/**
 * Whether to enable the raw renderer that utilizes raw port register writes for faster rendering.
 */
#define RAW_RENDERER false
