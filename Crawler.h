//
// Created by User on 19/03/2023.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#pragma once
#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, std::pair<int, int> position, int size, int hopLength, float speed);


    void move();

private:

    Direction getRandomDirection() const;

    std::pair<int, int> getNextPosition() const;

    bool isValidPosition(const std::pair<int, int>& position) const;

    Direction direction;
};
#endif // CRAWLER_H


