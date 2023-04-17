//
// Created by User on 16/04/2023.
//

#include "Scorpion.h"
#include <random>
#include <string>


const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells
static const int MAX_ATTEMPTS = 5;

Scorpion::Scorpion(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path)
        : Bug(id, position.first, position.second, direction, size, alive, path) {
    this->m_color = sf::Color::Yellow;
}

void Scorpion::move() {
    pair<int, int> newPosition = getNextPosition();
    bool isValid = isValidPosition(newPosition);
    int numAttempts = 0;
    while (!isValid && numAttempts < MAX_ATTEMPTS) {
        direction = getRandomDirection();
        newPosition = getNextPosition();
        isValid = isValidPosition(newPosition);
        numAttempts++;
    }
    if (isValid) {
        setPosition(newPosition);
        addToPath(newPosition);
    }
}

Direction Scorpion::getRandomDirection() const {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1, 6);
    int randInt = dis(gen);
    return static_cast<Direction>(randInt);
}

pair<int, int> Scorpion::getNextPosition() const {
    int scorpionX = getPosition().first;
    int scorpionY = getPosition().second;
    switch (direction) {
        case Direction::NORTH:
            scorpionY--;
            break;
        case Direction::EAST:
            scorpionX ++;
            break;
        case Direction::SOUTH:
            scorpionY++;
            break;
        case Direction::WEST:
            scorpionX --;
            break;
    }
    return make_pair(scorpionX, scorpionY);
}

bool Scorpion::isValidPosition(const pair<int, int>& position) const {
    int PositionX = position.first;
    int PositionY = position.second;
    return PositionX >= 0 && PositionX< BOARD_WIDTH && PositionY >= 0 && PositionY< BOARD_HEIGHT && !isOccupied(position);
}
