#pragma once

/**
 * The LED count of the cube along any axis.
 * For a 7x7x7 cube there is 343 total LEDs.
 */
#define CUBE_SIZE 7

/**
 * The rate to multiplex the entire cube at.
 * This sets the rate at which the entire cube renders a new frame.
 *
 * For example at 60 fps, the cube displays 60 distinct frames a second.
 * The internal multiplexing rate is higher to display each layer individually.
 */
#ifndef REFRESH_RATE
#define REFRESH_RATE 60
#endif

/**
 * Whether to enable the raw renderer that utilizes raw port register writes for faster rendering.
 */
#ifndef RAW_RENDERER
#define RAW_RENDERER false
#endif
