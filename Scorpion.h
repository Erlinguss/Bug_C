//
// Created by User on 16/04/2023.
//

#ifndef BUG_C_SCORPION_H
#define BUG_C_SCORPION_H

#include "Bug.h"
#include <random>
#include <SFML/Graphics.hpp>

class Scorpion : public Bug {
public:
    Scorpion(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path);
    void move() override;

private:

    Direction getRandomDirection() const;
    pair<int, int> getNextPosition() const;
    bool isValidPosition(const pair<int, int> &position) const;
};

#endif //BUG_C_SCORPION_H
