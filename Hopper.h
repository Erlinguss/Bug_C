

#ifndef BUG_C___HOPPER_H
#define BUG_C___HOPPER_H

#include "Bug.h"
#include <random>
#include <SFML/Graphics.hpp>

class Hopper : public Bug {
public:
    Hopper(int id, pair<int, int> position, Direction direction, int size, int hopLength, bool alive, list<pair<int, int>> path);

    void move() override;
    const pair<int, int> getDirection() const;
    int getHopLength() const;

private:
    int hopLength;
    void setRandomDirection();
    bool canHop(const std::pair<int, int>& direction) const;
};

#endif //BUG_C___HOPPER_H