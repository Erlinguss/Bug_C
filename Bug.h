//
// Created by User on 19/03/2023.
//

#ifndef BUG_C_BUG_H
#define BUG_C_BUG_H

#include<iostream>
#include <list>

enum class Direction { NORTH, EAST, SOUTH, WEST };
class Bug {

public:
    Bug(int id, int x, int y, Direction direction, int size);

    virtual ~Bug() {}

    int getId() const;
    std::pair<int, int> getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const std::list<std::pair<int, int>>& getPath() const;

    void setId(int id);
    void setPosition(const std::pair<int, int>& position);
    void setDirection(Direction direction);
    void setSize(int size);
    void setAlive(bool alive);
    void addToPath(const std::pair<int, int>& position);

    virtual void move() = 0;

    bool isWayBlocked() const;

private:
    int id;
    std::pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    std::list<std::pair<int, int>> path;

    bool isOccupied(const std::pair<int, int>& position) const;
    bool isWayBlocked(int board_size) const;

};

#endif //BUG_C_BUG_H
