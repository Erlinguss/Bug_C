//
// Created by User on 19/03/2023.
//

#include <utility>
#include<iostream>
#include <string>
#include "Bug.h"
using namespace std;


Bug::Bug(int id, int x, int y, Direction direction, int size, bool alive,  list<pair<int, int>> path)
        : id(id), position(std::make_pair(x, y)), direction(direction), size(size), alive(true) , path(path) {
    this->path = path;
    this->alive = alive;
}

int Bug::getId() const {
    return this-> id;
}

int Bug::getHopLength() const{
    return this-> hopLength;
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

//void Bug::BugData() {
//
//    string BugAlive = (this->alive ? "Alive" : "Dead");
//
//    string BugDirection;
//    switch (this->direction) {
//        case Direction::NORTH:
//            BugDirection = "North";
//            break;
//        case Direction::EAST:
//            BugDirection = "East";
//            break;
//        case Direction::SOUTH:
//            BugDirection = "South";
//            break;
//        case Direction::WEST:
//            BugDirection = "West";
//            break;
//        default:
//            BugDirection = "UNKNOWN";
//            break;
//
//            if (this->type == "Crawler") {
//                cout << "Crawler " << this->getId() << " at (" << this->getPosition().first << ","
//                     << this->getPosition().second
//                     << ") " << BugDirection << " size " << this->getSize() << " " << this->getHopLength() << " "
//                     << BugAlive << endl;
//            } else if (this->type == "Hopper") {
//                cout << "Hopper " << this->getId() << " at (" << this->getPosition().first << ","
//                     << this->getPosition().second
//                     << ") " << BugDirection << " size " << this->getSize() << " " << this->getHopLength() << " "
//                     << BugAlive << " hop length "
//                     << this->getHopLength() << endl;
//            } else if (this->type == "SuperBug") {
//                cout << "SuperBug " << this->getId() << " at (" << this->getPosition().first << ","
//                     << this->getPosition().second
//                     << ") " << BugDirection << " size " << this->getSize() << " " << this->getHopLength() << " "
//                     << BugAlive << endl;
//            }
//    }
//}

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
        for (auto& bug : m_bugs) {
            bug->move();
        }

        // Implement the fight/eat behavior
        for (auto& bug : m_bugs) {
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

    bool win =" " ;/* randomly determine if this bug wins or loses */

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
        cout << "Bug " << getType() << " loses the fight." << endl;
    }
}

Bug* Bug::eat(Bug& otherBug) {
    if (this->getSize() != otherBug.getSize()) {
        Bug* biggerBug = (this->getSize() > otherBug.getSize()) ? this : &otherBug;
        Bug* smallerBug = (this->getSize() < otherBug.getSize()) ? this : &otherBug;
        smallerBug->setAlive(false);
        biggerBug->setSize(biggerBug->getSize() + smallerBug->getSize());
        cout << "Bug " << biggerBug->getId() << " ate bug " << smallerBug->getId() << endl;
        return biggerBug;
    } else {
        cout << "Bug " << this->getId() << " and bug " << otherBug.getId() << " are with the same size and cannot eat each other" << endl;
        return nullptr;
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

