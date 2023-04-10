//
// Created by User on 19/03/2023.
//

#ifndef BUG_C_BUG_H
#define BUG_C_BUG_H

#include<iostream>
#include <list>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>


enum class Direction { NORTH, EAST, SOUTH, WEST };

class Bug {
public:
    Bug(int id, int x, int y, Direction direction, int size, int hopLength, std::string status);

    virtual ~Bug() {}

    int getId() const;
    std::pair<int, int> getPosition() const;
    Direction getDirection() const;
    int getHopLength() const;
    std::string getStatus() const;

    int getSize() const;
    bool isAlive() const;
    const std::list<std::pair<int, int>>& getPath() const;

    void setId(int id);
    void setPosition(const std::pair<int, int>& position);
    void setDirection(Direction direction);
    void setSize(int size);
    void setAlive(bool alive);
    void addToPath(const std::pair<int, int>& position);
    void setHopLength( int hopLength);
    void setStatus(const std::string& status);

    virtual void move() = 0;

    bool isWayBlocked() const;

    const sf::Color &getColor();

    long getType();

    void tap();

    void collide(Bug *pBug);
    bool isOccupied(const std::pair<int, int>& position) const;

    void eat(int i);

protected:

    int id;
    std::pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    std::list<std::pair<int, int>> path;
    int hopLength;
    std::string status;


    bool isWayBlocked(int board_size) const;

    bool m_tapped;
    sf::Color m_color;
    long m_type;

};

#endif //BUG_C_BUG_H
