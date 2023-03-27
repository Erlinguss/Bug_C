

#ifndef BUG_C___HOPPER_H
#define BUG_C___HOPPER_H

#include "Bug.h"
#include <random>

class Hopper : public Bug {
public:
    Hopper(int id, std::pair<int, int> position, int size, sf::Color color, int hopLength, float speed);

    void move() override;

    void setRandomDirection();

private:
    int hopLength;
    int hopCount;
    Direction direction;

    std::pair<int, int> getDirection() const;
    bool canHop(const std::pair<int, int>& direction) const;
};

#endif //BUG_C___HOPPER_H