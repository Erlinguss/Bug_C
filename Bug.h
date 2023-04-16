//
// Created by User on 19/03/2023.
//

#ifndef BUG_C_BUG_H
#define BUG_C_BUG_H

#include<iostream>
#include <list>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

using namespace std;


enum class Direction { NORTH , EAST , SOUTH, WEST };

class Bug {
public:
    Bug(int id, int x, int y, Direction direction, int size,  bool alive, const list<pair<int, int>> path);

    virtual ~Bug() {}

    int getId() const;
    pair<int, int> getPosition() const;
    Direction getDirection() const;
    int getHopLength() const;
    int getSize() const;
    bool isAlive() const;
    const list<pair<int, int>>& getPath() const;
    void setId(int id);
    void setPosition(const std::pair<int, int>& position);
    void setDirection(Direction direction);
    void setSize(int size);
    void setAlive(bool alive);
    void addToPath(const std::pair<int, int>& position);


//    virtual void move() = 0;
    virtual void move();
    bool isWayBlocked() const;
    const sf::Color &getColor() const;
    string getType() const;
    void  setType(string type);
    void tap();
    void collide(Bug *pBug);
    bool isOccupied(const std::pair<int, int>& position) const;
    Bug * eat(Bug& otherBug);

    // Initialize m_bugs as an empty vector
    vector<Bug*> bugs;

    void BugData();

protected:

    int id;
    std::pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int, int>> path;
    int hopLength;
    string status;
    string type;
    bool isWayBlocked(int board_size) const;
    bool m_tapped;
    sf::Color m_color;

    void fight();

};

#endif //BUG_C_BUG_H
