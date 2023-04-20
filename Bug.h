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


enum class Direction { NORTH , EAST , SOUTH , WEST  };

class Bug {
public:
    Bug(int id, int x, int y, Direction direction, int size,  bool alive, const list<pair<int, int>> path);


    virtual ~Bug() {}
    virtual void move();
    virtual int getHopLength();
    virtual void BugData();

    int getId() const;
    int getHopLength() const;
    int getSize() const;

    void setId(int id);
    void setPosition(const std::pair<int, int>& position);
    void setDirection(Direction direction);
    void setSize(int size);
    void setAlive(bool alive);
    void addToPath(const std::pair<int, int>& position);
    void  setType(string type);
    void tap();
    void collide(Bug *pBug);
    bool isOccupied(const std::pair<int, int>& position) const;
    void eat(int i);

    bool isAlive() const;
    bool isWayBlocked()
    {
        isWayBlocked(10);
        return false;
    }

    const sf::Color &getColor() const;
    const list<pair<int, int>>& getPath() const;

    string getType() const;

    vector<Bug*> bugs;

    Direction getDirection() const;
    pair<int, int> getPosition() const;


protected:

    int id;
    int hopLength;
    int size;
    std::pair<int, int> position;
    Direction direction;

    bool alive;
    bool isWayBlocked(int board_size) const;
    bool m_tapped;

    list<pair<int, int>> path;
    string status;
    string type;

    sf::Color m_color;


};

#endif //BUG_C_BUG_H
