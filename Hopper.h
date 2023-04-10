

#ifndef BUG_C___HOPPER_H
#define BUG_C___HOPPER_H

#include "Bug.h"
#include <random>
#include <SFML/Graphics.hpp>

class Hopper : public Bug {
public:
    Hopper(int id, std::pair<int, int> position,Direction direction, int size,  int hopLength, std::string status);

    void move() override;

    void setRandomDirection();

private:
    int hopLength;
    Direction direction;

    std::pair<int, int> getDirection() const;
    bool canHop(const std::pair<int, int>& direction) const;
};

#endif //BUG_C___HOPPER_H