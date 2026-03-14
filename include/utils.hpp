#pragma once

#include <Arduino.h>

inline uint32_t sat_add_uint32(const uint32_t a, const uint32_t b) {
    uint32_t res = a + b;
    res |= -(res < a);
    return res;
}

inline uint32_t sat_sub_uint32(const uint32_t a, const uint32_t b) {
    uint32_t res = a - b;
    res &= -(res <= a);
    return res;
}

inline double randomDouble(double min, double max) {
    return min + random(1UL << 31) * (max - min) / (1UL << 31); // Use 1ULL<<63 for max double values
}
