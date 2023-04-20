//
// Created by User on 20/04/2023.
//
#include <random>
#include "SuperBug.h"
const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

SuperBug::SuperBug(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path )
        : Bug(id, position.first, position.second, direction, size, alive, path)
{
    this->m_color = sf::Color::Blue;
}

void SuperBug::move() {
    pair<int, int> newPosition = getNextPosition();
    while (!isValidPosition(newPosition)) {
        direction = getRandomDirection();
        newPosition = getNextPosition();
    }
    setPosition(newPosition);
    addToPath(newPosition);
}

Direction SuperBug::getRandomDirection() const {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 3);
    int randInt = dis(gen);
    return static_cast<Direction>(randInt);
}

pair<int, int> SuperBug::getNextPosition() const {
    int crawlerX = getPosition().first;
    int crawlerY = getPosition().second;
    switch (direction) {
        case Direction::NORTH:
            crawlerY--;
            break;
        case Direction::EAST:
            crawlerX++;
            break;
        case Direction::SOUTH:
            crawlerY++;
            break;
        case Direction::WEST:
            crawlerX--;
            break;
    }
    return make_pair(crawlerX, crawlerY);
}

bool SuperBug::isValidPosition(const pair<int, int>& position) const {
    int PositionX = position.first;
    int PositionY = position.second;
    return PositionX >= 0 && PositionX< BOARD_WIDTH && PositionY >= 0 && PositionY< BOARD_HEIGHT && !isOccupied(position);
}
