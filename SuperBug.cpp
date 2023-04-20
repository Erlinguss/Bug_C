//
// Created by User on 20/04/2023.
//
#include <random>
#include "SuperBug.h"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

SuperBug::SuperBug(int id, pair<int, int> position, Direction direction, int size, bool alive,
                   list<pair<int, int>> path)
        : Bug(id, position.first, position.second, direction, size, alive, path) {
    this->m_color = sf::Color::Blue;
}

/*=======================================================
         METHOD TO MOVE THE SUPER BUG SEPARATELY
              FROM THE REST OF THE BUGS
========================================================*/
void SuperBug::move(int x, int y) {
    pair<int, int> newPosition = getPosition();
    newPosition.first += x;
    newPosition.second += y;

    if (newPosition.first < 0) {
        newPosition.first = 0;
    }

    if (newPosition.first > 9) {
        newPosition.first = 9;
    }

    if (newPosition.second < 0) {
        newPosition.second = 0;
    }

    if (newPosition.second > 9) {
        newPosition.second = 9;
    }
    this->setPosition(newPosition);
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

/*=======================================================
          METHOD TO GET A RANDOM DIRECTION
========================================================*/
Direction SuperBug::getRandomDirection() const {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 3);
    int randInt = dis(gen);
    return static_cast<Direction>(randInt);
}

pair<int, int> SuperBug::getNextPosition() const {
    int SuperBugX = getPosition().first;
    int SuperBugY = getPosition().second;
    switch (direction) {
        case Direction::NORTH:
            SuperBugY--;
            break;
        case Direction::EAST:
            SuperBugX++;
            break;
        case Direction::SOUTH:
            SuperBugY++;
            break;
        case Direction::WEST:
            SuperBugX--;
            break;
    }
    return make_pair(SuperBugX, SuperBugY);
}

/*=======================================================
     METHOD TO CHECK IF THERE IS A VALID POSITION
========================================================*/
bool SuperBug::isValidPosition(const pair<int, int> &position) const {
    int PositionX = position.first;
    int PositionY = position.second;
    return PositionX >= 0 && PositionX < BOARD_WIDTH && PositionY >= 0 && PositionY < BOARD_HEIGHT &&
           !isOccupied(position);
}
