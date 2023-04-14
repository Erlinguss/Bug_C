//
// Created by User on 19/03/2023.
//
#include "Crawler.h"
#include <random>
#include <string>

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

Crawler::Crawler(int id, pair<int, int> position, Direction direction, int size, int hopLength, bool alive)
        : Bug(id, position.first, position.second, getRandomDirection(), size, hopLength, alive)

{
    this->m_color = sf::Color::Green;
}

void Crawler::move() {
    pair<int, int> newPosition = getNextPosition();
    while (!isValidPosition(newPosition)) {
        direction = getRandomDirection();
        newPosition = getNextPosition();
    }
    setPosition(newPosition);
    addToPath(newPosition);
}

Direction Crawler::getRandomDirection() const {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 3);
    int randInt = dis(gen);
    return static_cast<Direction>(randInt);
}

 pair<int, int> Crawler::getNextPosition() const {
    int x = getPosition().first;
    int y = getPosition().second;
    switch (direction) {
        case Direction::NORTH:
            y--;
            break;
        case Direction::EAST:
            x++;
            break;
        case Direction::SOUTH:
            y++;
            break;
        case Direction::WEST:
            x--;
            break;
    }
    return make_pair(x, y);
}

bool Crawler::isValidPosition(const pair<int, int>& position) const {
    int x = position.first;
    int y = position.second;
    return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && !isOccupied(position);
}

