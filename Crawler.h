//
// Created by User on 19/03/2023.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#pragma once
#include "Bug.h"
#include <string>


class Crawler : public Bug {
public:
    Crawler(int id, pair<int, int> position, Direction direction,int size, int hopLength, bool alive);

    void move() override;

private:

    Direction getRandomDirection() const;

    pair<int, int> getNextPosition() const;

    bool isValidPosition(const pair<int, int>& position) const;

    Direction direction;
};
#endif // CRAWLER_H


