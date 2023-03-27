//
// Created by User on 19/03/2023.
//
#include <utility>
#include<iostream>
#include "Bug.h"

Bug::Bug(int id, int x, int y, Direction direction, int size)
        : id(id), position(std::make_pair(x, y)), direction(direction), size(size), alive(true) {}

int Bug::getId() const {
    return id;
}

std::pair<int, int> Bug::getPosition() const {
    return position;
}

Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return size;
}

bool Bug::isAlive() const {
    return alive;
}

void Bug::setAlive(bool alive) {
    this->alive = alive;
}
const std::list<std::pair<int, int>>& Bug::getPath() const {
    return path;
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
            return false;
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
    }
}

const sf::Color& Bug::getColor() {
    return  m_color;
}

long Bug::getType() {
    return m_type;
}

void Bug::tap() {
    if (!m_tapped) {
        m_tapped = true;
        m_color = sf::Color::White;
    }
}

void Bug::collide(Bug *pBug) {
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