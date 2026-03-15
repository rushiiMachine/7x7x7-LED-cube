#include <vector>
#include "routines/Snake.hpp"
#include "utils.hpp"

constexpr uint32_t SPEED_US = 200 * 1000UL; // 200ms

void Snake::restart(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    memset(cube, 0, sizeof(*cube));
    head = {
        static_cast<uint8_t>(random(CUBE_SIZE)),
        static_cast<uint8_t>(random(CUBE_SIZE)),
        static_cast<uint8_t>(random(CUBE_SIZE)),
    };
    headDirection = Direction::randomDirection();
    (*cube)[head.x][head.y][head.z] = true;
}

Coordinate Snake::nextPosition(const Direction direction) const {
    const uint8_t x = head.x + direction.getX(),
            y = head.y + direction.getY(),
            z = head.z + direction.getZ();

    // Integer overflow is utilized here
    if (x >= CUBE_SIZE || y >= CUBE_SIZE || z >= CUBE_SIZE) return {};

    return {x, y, z};
}

bool Snake::move(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    const auto newHead = nextPosition(headDirection);

    if (!newHead.isValid || (*cube)[newHead.x][newHead.y][newHead.z]) {
        return turnAndMove(cube);
    }

    this->head = newHead;
    (*cube)[head.x][head.y][head.z] = true;

    return true;
}

bool Snake::turnAndMove(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    std::vector<Direction> directions = {
        {
            Direction::NORTH,
            Direction::WEST,
            Direction::SOUTH,
            Direction::EAST,
            Direction::UP,
            Direction::DOWN,
        }
    };

    while (!directions.empty()) {
        const auto idx = random(directions.size());
        const auto direction = directions[idx];

        // Cannot go backwards or forwards
        if (direction == this->headDirection ||
            direction == this->headDirection.opposite()
        ) {
            directions.erase(directions.begin() + idx);
            continue;
        }

        const auto newHead = nextPosition(direction);

        if (!newHead.isValid || (*cube)[newHead.x][newHead.y][newHead.z]) {
            directions.erase(directions.begin() + idx);
            continue;
        }

        this->head = newHead;
        this->headDirection = direction;
        (*cube)[head.x][head.y][head.z] = true;
        return true;
    }

    // Could not find
    return false;
}

void Snake::setup(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    restart(cube);
}

void Snake::update(boolean (*cube)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE], unsigned long dt) {
    if ((elapsedOverflowUs += dt) < SPEED_US) return;
    elapsedOverflowUs -= SPEED_US;

    // Random chance of turning (1/8)
    if (random(8) == 0 && !turnAndMove(cube)) {
        restart(cube);
        return;
    }

    // Move head forward
    if (!move(cube)) {
        restart(cube);
    }
}
