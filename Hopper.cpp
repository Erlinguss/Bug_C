

#include "Hopper.h"

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

Hopper::Hopper(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path,  int hopLength)
: Bug(id, position.first, position.second, direction, size, alive, path) , hopLength(hopLength) {
    this->m_color = sf::Color::Red;
}

int Hopper::getHopLength()  const  {
    return this->hopLength;
}

void Hopper::setHopLength(int hopLength) {
    this->hopLength = hopLength;
}

void Hopper::move() {
    pair<int, int> Direction_X_Y = getDirection();
    int directionX = Direction_X_Y.first;
    int directionY = Direction_X_Y.second;

    if (canHop(Direction_X_Y)) {
        int newDirectionX = position.first + directionX * hopLength;
        int newDirectionY = position.second + directionY * hopLength;
        setPosition(make_pair(newDirectionX, newDirectionY));
        addToPath(getPosition());
    }
    else {
        setRandomDirection();
    }
}

void Hopper::setRandomDirection() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1, 4);
    int randInt = dis(gen);
    direction = static_cast<Direction>(randInt);
}

const pair<int, int> Hopper::getDirection() const {
    int hopperX = 0, hopperY = 0;
    switch (direction) {
        case Direction::NORTH:
            hopperY = -1;
            break;
        case Direction::EAST:
            hopperX = 1;
            break;
        case Direction::SOUTH:
            hopperY = 1;
            break;
        case Direction::WEST:
            hopperX = -1;
            break;
    }
    return make_pair( hopperX, hopperY);
}

bool Hopper::canHop(const std::pair<int, int>& direction) const {
    int hopperX = direction.first;
    int hopperY = direction.second;

    for (int i = 1; i <= hopLength; i++) {
        int newHopperX = position.first + i*hopperX;
        int newHopperY = position.second + i*hopperY;
        if (newHopperX  < 0 || newHopperX  >= BOARD_WIDTH || newHopperY < 0 || newHopperY >= BOARD_HEIGHT) {
            return false;
        }

        if (isOccupied(make_pair(newHopperX , newHopperY))) {
            return false;
        }
    }
    return true;
}
