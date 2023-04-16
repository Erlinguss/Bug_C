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
    void setRandomDirection();
    bool canMove(const pair<int, int> &direction) const;

private:

};

#endif //BUG_C_SCORPION_H
