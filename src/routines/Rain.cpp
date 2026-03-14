#include "routines/Rain.hpp"
#include "utils.hpp"

constexpr uint32_t GRAVITY_US = 75 * 1000UL; // 75ms
constexpr uint32_t STICKY_RAIN_US = 1000 * 1000UL; // 1s
constexpr uint32_t SPAWN_US = 250 * 1000UL; // 250ms
constexpr uint8_t SPAWN_COUNT = 5; // Up to 4 droplets per spawn

void Rain::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], const unsigned long dt) {
    for (int x = 0; x < CUBE_SIZE; ++x) {
        for (int y = 0; y < CUBE_SIZE; ++y) {
            for (int z = 0; z < CUBE_SIZE; ++z) {
                const auto time = pixelTimesUs[x][y][z];
                if (time == 0) {
                    (*cube)[x][y][z] = false;
                    continue;
                }

                // Decrease time left for pixel
                if ((pixelTimesUs[x][y][z] = sat_sub_uint32(time, dt)) > 0) {
                    (*cube)[x][y][z] = true;
                    continue;
                }

                // Randomly allow pixels at bottom to linger recursively
                if (z == 0) {
                    if (random(2) == 0) {
                        pixelTimesUs[x][y][z] = random(STICKY_RAIN_US) + 1;
                        (*cube)[x][y][z] = true;
                    } else {
                        (*cube)[x][y][0] = false;
                    }
                    continue;
                }

                // Move pixel downwards
                pixelTimesUs[x][y][z - 1] = static_cast<uint32_t>(GRAVITY_US * pixelSpeeds[x][y]);
                (*cube)[x][y][z - 1] = true;
                (*cube)[x][y][z] = false;
            }
        }
    }

    // Spawn new pixels once timer triggers
    if ((spawnDelay = sat_sub_uint32(spawnDelay, dt)) == 0) {
        spawnDelay = SPAWN_US;

        const uint8_t count = random(SPAWN_COUNT);

        for (auto i = 0; i < count; ++i) {
            const auto x = random(CUBE_SIZE);
            const auto y = random(CUBE_SIZE);
            constexpr auto z = CUBE_SIZE - 1;
            const float speed = randomDouble(0.8f, 1.8f);

            (*cube)[x][y][z] = true;
            pixelSpeeds[x][y] = speed;
            pixelTimesUs[x][y][z] = static_cast<uint32_t>(GRAVITY_US * speed);
        }
    }
}
