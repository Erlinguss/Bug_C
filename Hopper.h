

#ifndef BUG_C___HOPPER_H
#define BUG_C___HOPPER_H

#include "Bug.h"
#include <random>
#include <SFML/Graphics.hpp>

class Hopper : public Bug {
public:
    Hopper(int id, pair<int, int> position,Direction direction, int size,  int hopLength, bool alive,  list<pair<int, int>> path);

    void move() override;
    //int hopLength();
    Direction direction;
    void setRandomDirection();
    pair<int, int> getDirection() const;
    bool canHop(const std::pair<int, int>& direction) const;
    int getHopLength();


private:


   // int getHopLength();
};

#endif //BUG_C___HOPPER_H