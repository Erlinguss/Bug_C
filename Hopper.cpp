

#include "Hopper.h"

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

Hopper::Hopper(int id, std::pair<int, int> position, Direction direction, int size, int hopLength, std::string status)
: Bug(id, position.first, position.second, direction, size, hopLength, status) {
    this->m_color = sf::Color::Red;
}

void Hopper::move() {
    std::pair<int, int> dx_dy = getDirection();
    int dx = dx_dy.first;
    int dy = dx_dy.second;

    if (canHop(dx_dy)) {
        int newX = position.first + dx * hopLength;
        int newY = position.second + dy * hopLength;
        setPosition(std::make_pair(newX, newY));
        addToPath(getPosition());
    }
    else {
        setRandomDirection();
    }
}

void Hopper::setRandomDirection() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 4);
    int randInt = dis(gen);
    direction = static_cast<Direction>(randInt);
}

std::pair<int, int> Hopper::getDirection() const {
    int dx = 0, dy = 0;
    switch (direction) {
        case Direction::NORTH:
            dy = -1;
            break;
        case Direction::EAST:
            dx = 1;
            break;
        case Direction::SOUTH:
            dy = 1;
            break;
        case Direction::WEST:
            dx = -1;
            break;
    }
    return std::make_pair(dx, dy);
}

bool Hopper::canHop(const std::pair<int, int>& direction) const {
    int dx = direction.first;
    int dy = direction.second;

    for (int i = 1; i <= hopLength; i++) {
        int newX = position.first + i*dx;
        int newY = position.second + i*dy;
        if (newX < 0 || newX >= BOARD_WIDTH || newY < 0 || newY >= BOARD_HEIGHT) {
            return false;
        }

        if (isOccupied(std::make_pair(newX, newY))) {
            return false;
        }
    }
    return true;
}
