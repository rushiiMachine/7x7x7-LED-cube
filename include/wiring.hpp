#pragma once

#include <Arduino.h>

/**
 * Whether to enable the raw renderer that utilizes raw port register writes for faster rendering.
 * This does not work with the pin remapping config below.
 */
#ifndef RAW_RENDERER
#define RAW_RENDERER false
#endif

/**
 * An unused floating analog pin that is used for seeding RNG.
 * Default is A15 aka. D69.
 */
constexpr uint8_t SEED_PIN = A15;

/**
 * Pin used for the button to switch routines.
 * Default is A7 aka. D61.
 */
constexpr uint8_t BUTTON_PIN = A7;

// #ifndef LAYER_REMAPPING
// #define LAYER_REMAPPING
// /**
//  * Remap layers to different Arduino pins for use with
//  * the standard renderer. By default, no remapping is done,
//  * and each layer (from bottom up) is wired from A0 to A6.
//  */
// constexpr uint8_t LAYER_PIN_MAPPING[CUBE_SIZE] = {
//     A0, A1, A2, A3, A4, A5, A6,
// };
// #endif

// #ifndef COLUMN_REMAPPING
// #define COLUMN_REMAPPING
// /**
//  * Remap columns to different Arduino pins for use with
//  * the standard renderer. By default, no remapping is done,
//  * and each column is wired in increasing order: the origin (0,0,0)
//  * at the cube's bottom front left corner is wired to D0, and this increases
//  * sequentially on the x-axis to the right, then the y-axis to the rear, with the
//  * very end of the cube, the rear right corner being wired to D48.
//  *
//  * This remapping array represents a top-down view of the cube, with the
//  * bottom being the front of the cube, and the top being the rear.
//  */
// const uint8_t COLUMN_PIN_MAPPING[CUBE_SIZE][CUBE_SIZE] = {
//     /* y: 6 */ {42, 43, 44, 45, 46, 47, 48},
//     /* y: 5 */ {35, 36, 37, 38, 39, 40, 41},
//     /* y: 4 */ {28, 29, 30, 31, 32, 33, 34},
//     /* y: 3 */ {21, 22, 23, 24, 25, 26, 27}, // ^ y-axis
//     /* y: 2 */ {14, 15, 16, 17, 18, 19, 20}, // > x-axis
//     /* y: 1 */ {7, 8, 9, 10, 11, 12, 13},
//     /* y: 0 */ {0, 1, 2, 3, 4, 5, 6},
//     /* x:       0   1   2   3   4   5   6 */
// };
// #endif
