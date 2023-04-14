//
// Created by User on 19/03/2023.
//

#include <utility>
#include<iostream>
#include "Bug.h"

//
Bug::Bug(int id, int x, int y, Direction direction, int size, int hopLength, bool alive)
        : id(id), position(std::make_pair(x, y)), direction(direction), size(size), hopLength(hopLength), alive(true) {

}

int Bug::getId() const {
    return this-> id;
}

int Bug::getHopLength() const{
    return this-> hopLength;
}

string Bug::getStatus() const{
    return this-> status;
}

pair<int, int> Bug::getPosition() const {
    return position;
}

Direction Bug::getDirection() const {
    return this -> direction;
}

int Bug::getSize() const {
    return this-> size;
}

void Bug::setSize(int size) {
    this ->size =size;
}

bool Bug::isAlive() const {
    return this -> alive;
}

void Bug::setAlive(bool alive) {
    this->alive = alive;
}

const list<std::pair<int, int>>& Bug::getPath() const {
    return this-> path;
}

string Bug::getType() const{
    return this->type;
}

void Bug:: setType(string type){
    this->type= type;
}


bool Bug::isWayBlocked(int board_size) const {
    switch (direction) {
        case Direction::NORTH:
            return position.first == 0;
        case Direction::EAST:
            return position.second == board_size - 1;
        case Direction::SOUTH:
            return position.first == board_size - 1;
        case Direction::WEST:
            return position.second == 0;
        default:
            throw std::runtime_error("Invalid direction");
    }
}

void Bug::move() {
    path.push_back(getPosition());
    switch (direction) {
        case Direction::NORTH:
            position.first--;
            break;
        case Direction::EAST:
            position.second++;
            break;
        case Direction::SOUTH:
            position.first++;
            break;
        case Direction::WEST:
            position.second--;
            break;
        default:
            throw std::runtime_error("Invalid direction");
    }
}

const sf::Color& Bug::getColor() {
    return  m_color;
}



void Bug::tap() {
    if (!m_tapped) {
        m_tapped = true;

        move();
        // implement the move, and the fight
    }
}

void Bug::collide(Bug* pBug) {
    if (pBug != nullptr) {
        if (pBug->isAlive() && isAlive()) {
            setAlive(false);
            pBug->setAlive(false);
            m_color = sf::Color::Yellow;
            pBug->m_color = sf::Color::Yellow;
        }
    }
}

void Bug::addToPath(const std::pair<int, int>& point) {
    path.push_back(point);
}

void Bug::setPosition(const std::pair<int, int>& new_position) {
    position = new_position;
}

bool Bug::isOccupied(const std::pair<int, int>& position) const {
    return (getPosition() == position);
}

void Bug::eat(int i) {
    // implement the eat function
}