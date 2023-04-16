//
// Created by User on 19/03/2023.
//

#include <utility>
#include<iostream>
#include <string>
#include "Bug.h"
using namespace std;


Bug::Bug(int id, int x, int y, Direction direction, int size, bool alive,  list<pair<int, int>> path)
        : id(id), position(std::make_pair(x, y)), direction(direction), size(size), alive(true) , path(path)  {
    this->path = path;
//    this->alive = alive;

}

int Bug::getId() const {
    return this-> id;
}

int Bug::getHopLength() {
    return this->hopLength;
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

void Bug::addToPath(const std::pair<int, int>& point) {
    path.push_back(point);
}

void Bug::setPosition(const std::pair<int, int>& new_position) {
    position = new_position;
}

bool Bug::isOccupied(const std::pair<int, int>& position) const {
    return (getPosition() == position);
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

void Bug::BugData() {

    enum direction {
        NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4
    };

    string BugAlive = (this->alive ? "Alive" : "Dead");

    string BugDirection;
    switch (this->direction) {
        case Direction::NORTH:
            BugDirection = "North";
            break;
        case Direction::EAST:
            BugDirection = "East";
            break;
        case Direction::SOUTH:
            BugDirection = "South";
            break;
        case Direction::WEST:
            BugDirection = "West";
            break;
        default:
            BugDirection = "UNKNOWN";
            break;
    }
            if (this->type == "Crawler") {
                cout << this->getId() << "\t" << type
                     << "\t\t(" << this->getPosition().first << "," << this->getPosition().second
                     << ")\t\t"
                     << BugDirection
                     << "\t\t\t" << this->getSize()
                     << "\t\t\t-"
                     << "\t\t\t" << BugAlive  << endl;

            } else if (this->type == "Hopper") {
                cout << this->getId() << "\t" << type
                     << "\t\t(" << this->getPosition().first << "," << this->getPosition().second
                     << ")\t\t"
                     << BugDirection
                     << "\t\t\t" << this->getSize()
                     << "\t\t\t" << this->getHopLength()
                     << "\t\t\t" << BugAlive  << endl;

            } else if (this->type == "SuperBug") {
                cout << this->getId() << "\t" << type
                     << "\t\t(" << this->getPosition().first << "," << this->getPosition().second
                     << ")\t\t"
                     << BugDirection
                     << "\t\t\t" << this->getSize()
                     << "\t\t\t-"
                     << "\t\t\t" << BugAlive  << endl;
            }
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

const sf::Color& Bug::getColor() const {
    return  m_color;
}


void Bug::tap() {
    if (!m_tapped) {
        m_tapped = true;

        // Call move() on all bugs
        for (auto& bug : bugs) {
            bug->move();
        }

        // Implement the fight/eat behavior
        for (auto& bug : bugs) {
            if (bug->type == "Crawler") {
                bug->fight();  // Call fight() for Crawler bugs
            } else if (bug->type == "Hopper") {
                Bug &otherBug = (Bug &) " ";
                bug->eat( otherBug);   // Call eat() for Hopper bugs
            }
        }
    }
}


void Bug::fight() {
    bool win = false; // randomly determine if this bug wins or loses

    int m_health;
    int m_attackPower;
    if (win) {
        // Update internal state for winning bug
        m_health += 10;  // Increase health by 10
        m_attackPower += 5;  // Increase attack power by 5
        cout << "Bug " << getType() << " wins the fight!" << endl;
    } else {
        // Update internal state for losing bug
        m_health -= 5;  // Decrease health by 5
        m_attackPower -= 2;  // Decrease attack power by 2
        cout << "Bug " << getType() << " loses the fight!" << endl;
    }
}

Bug * Bug::eat(Bug& otherBug) {
    int m_health;
    int m_attackPower;
    if (otherBug.isAlive()) {
        // Update internal state for eating bug
        m_health += 5;  // Increase health by 5
        m_attackPower += 2;  // Increase attack power by 2
        otherBug.setAlive(false);  // Set otherBug as dead
        cout << "Bug " << getType() << " eats bug " << otherBug.getType() << "!" << endl;
    } else {
        cout << "Bug " << getType() << " cannot eat bug " << otherBug.getType() << " as it is already dead!" << endl;
    }
}





