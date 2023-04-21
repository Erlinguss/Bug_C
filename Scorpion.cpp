//
// Created by User on 16/04/2023.
//

#include "Scorpion.h"
#include <random>
#include <string>


const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;
static const int MAX_ATTEMPTS = 5;

Scorpion::Scorpion(int id, pair<int, int> position, Direction direction, int size, bool alive,
                   list<pair<int, int>> path)
        : Bug(id, position.first, position.second, direction, size, alive, path) {
    this->m_color = sf::Color::Yellow;
}

/*=======================================================
             METHOD TO MOVE THE SCORPION
========================================================*/
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

/*=======================================================
          METHOD TO GET A RANDOM DIRECTION
========================================================*/
Direction Scorpion::getRandomDirection() const {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 3);
    int randInt = dis(gen);
    return static_cast<Direction>(randInt);
}// cppreference. (n.d.). random_device. Retrieved April 16, 2023, from https://en.cppreference.com/w/cpp/numeric/random/random_device

pair<int, int> Scorpion::getNextPosition() const {
    int scorpionX = getPosition().first;
    int scorpionY = getPosition().second;
    switch (direction) {
        case Direction::NORTH:
            scorpionY--;
            break;
        case Direction::EAST:
            scorpionX++;
            break;
        case Direction::SOUTH:
            scorpionY++;
            break;
        case Direction::WEST:
            scorpionX--;
            break;
    }
    return make_pair(scorpionX, scorpionY);
}


/*=======================================================
     METHOD TO CHECK IF THERE IS A VALID POSITION
========================================================*/
bool Scorpion::isValidPosition(const pair<int, int> &position) const {
    int PositionX = position.first;
    int PositionY = position.second;
    return PositionX >= 0 && PositionX <  BOARD_WIDTH && PositionY >= 0 && PositionY < BOARD_HEIGHT &&
           !isOccupied(position);
}
