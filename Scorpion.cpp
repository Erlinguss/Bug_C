//
// Created by User on 16/04/2023.
//

#include <random>
#include "Scorpion.h"


const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

Scorpion::Scorpion(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path)
        : Bug(id, position.first, position.second, direction, size, alive, path) {
    this->m_color = sf::Color::Yellow;
}


void Scorpion::move() {
    // Get the current position of the scorpion
    int currentX = getPosition().first;
    int currentY = getPosition().second;

    // Check if the scorpion has reached the end of its path
    if (getPath().empty()) {
        // If the scorpion has reached the end of its path, it stops moving
        return;
    }

    // Get the next target position from the path
    pair<int, int> nextTarget = getPath().front();

    // Calculate the direction to the next target position
    int directionX = 0;
    int directionY = 0;

    if (nextTarget.first > currentX) {
        directionX = 1;
    } else if (nextTarget.first < currentX) {
        directionX = -1;
    }

    if (nextTarget.second > currentY) {
        directionY = 1;
    } else if (nextTarget.second < currentY) {
        directionY = -1;
    }

    // Check if the way is blocked
    bool wayBlocked = isWayBlocked(BOARD_WIDTH);

    if (wayBlocked) {
        // If the way is blocked, set a random direction
        setRandomDirection();
    } else {
        // Check if the scorpion can move to the next target position
        if (canMove(make_pair(directionX, directionY))) {
            // Update the position of the scorpion
            int newDirectionX = currentX + directionX;
            int newDirectionY = currentY + directionY;
            setPosition(make_pair(newDirectionX, newDirectionY));
            addToPath(getPosition());
        } else {
            // If the scorpion cannot move to the next target position, set a random direction
            setRandomDirection();
        }
    }
}

void Scorpion::setRandomDirection() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1, 4);
    int randInt = dis(gen);
    direction = static_cast<Direction>(randInt);
}


        bool Scorpion::canMove(const std::pair<int, int>& direction) const {
            int scorpionX = direction.first;
            int scorpionY = direction.second;

            int newScorpionX = position.first + scorpionX;
            int newScorpionY = position.second + scorpionY;

            if (newScorpionX < 0 || newScorpionX >= BOARD_WIDTH || newScorpionY < 0 || newScorpionY >= BOARD_HEIGHT) {
                return false;
            }

            if (isOccupied(make_pair(newScorpionX, newScorpionY))) {
                return false;
            }

            return true;
        }


