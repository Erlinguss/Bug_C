//
// Created by User on 20/04/2023.
//

#ifndef BUG_C_SUPERBUG_H
#define BUG_C_SUPERBUG_H

#include "Bug.h"

class SuperBug : public Bug{
public:
 SuperBug(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path );

    void move() override;

private:

    Direction getRandomDirection() const;
    pair<int, int> getNextPosition() const;
    bool isValidPosition(const pair<int, int>& position) const;
    Direction direction;

};


#endif //BUG_C_SUPERBUG_H
