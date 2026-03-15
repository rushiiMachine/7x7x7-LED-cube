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

class Direction {
public:
    enum Value : char {
        NORTH = 'n',
        EAST = 'e',
        SOUTH = 's',
        WEST = 'w',
        UP = 'u',
        DOWN = 'd',
    };

    Direction() = default;

    // ReSharper disable once CppNonExplicitConvertingConstructor
    constexpr Direction(const Value direction) : value(direction) {
    }

    // Allow switch and comparisons.
    explicit constexpr operator Value() const { return value; }

    // Prevent usage: if(fruit)
    explicit operator bool() const = delete;

    constexpr bool operator==(Direction a) const { return value == a.value; }
    constexpr bool operator!=(Direction a) const { return value != a.value; }

    [[nodiscard]]
    constexpr int8_t getX() const {
        switch (value) {
            case EAST:
                return 1;
            case WEST:
                return -1;
            default:
                return 0;
        }
    }

    [[nodiscard]]
    constexpr int8_t getY() const {
        switch (value) {
            case NORTH:
                return 1;
            case SOUTH:
                return -1;
            default:
                return 0;
        }
    }

    [[nodiscard]]
    constexpr int8_t getZ() const {
        switch (value) {
            case UP:
                return 1;
            case DOWN:
                return -1;
            default:
                return 0;
        }
    }

    [[nodiscard]]
    constexpr Direction opposite() const {
        switch (value) {
            case NORTH:
                return SOUTH;
            case EAST:
                return WEST;
            case SOUTH:
                return NORTH;
            case WEST:
                return EAST;
            case UP:
                return DOWN;
            case DOWN:
                return UP;
            default:
                abort();
        }
    }

    static Direction randomDirection() {
        switch (random(6)) {
            case 0:
                return NORTH;
            case 1:
                return EAST;
            case 2:
                return SOUTH;
            case 3:
                return WEST;
            case 4:
                return UP;
            case 5:
                return DOWN;
            default:
                abort();
        }
    }

private:
    Value value;
};

struct Coordinate {
    bool isValid;
    uint8_t x = 0, y = 0, z = 0;

    Coordinate() : isValid(false) {
    }

    Coordinate(
        const uint8_t x,
        const uint8_t y,
        const uint8_t z
    ) : isValid(true), x(x), y(y), z(z) {
    }
};
