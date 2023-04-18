//
// Created by User on 19/03/2023.
//

#include <utility>
#include<iostream>
#include <string>
#include "Bug.h"
#include <iomanip>
#include <sstream>

using namespace std;


Bug::Bug(int id, int x, int y, Direction direction, int size, bool alive,  list<pair<int, int>> path)
        : id(id), position(std::make_pair(x, y)), direction(direction), size(size), alive(true) , path(path)  {
    this->path = path;

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
            if(size < pBug->getSize())
            {
                setAlive(false);
                m_color = sf::Color::Yellow;
                size += pBug->getSize();
            }
            else
            {
                pBug->setAlive(false);
                pBug->m_color = sf::Color::Yellow;
                pBug->setSize(pBug->getSize()+size);
            }
        }
    }
}



void Bug::BugData() {

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

// Set the column widths for each column
    int idColumnWidth = 4;
    int typeColumnWidth = 12;
    int positionColumnWidth = 12;
    int directionColumnWidth = 16;
    int sizeColumnWidth = 12;
    int ColumnWidth = 13;
    int statusColumnWidth = 10;


// Common parts of the output string
    std::ostringstream oss;
    oss << setw(idColumnWidth) << left << std::to_string(this->getId())
        << setw(typeColumnWidth) << left << type
        << setw(positionColumnWidth) << left << "(" + std::to_string(this->getPosition().first) + "," +
                                                          std::to_string(this->getPosition().second) + ")"
        << std::setw(directionColumnWidth) << std::left << BugDirection
        << std::setw(sizeColumnWidth) << std::left << std::to_string(this->getSize());

// Append varying parts based on bug type
    if (this->type == "Crawler") {
        oss << setw(ColumnWidth) << left << "-"
            << setw(statusColumnWidth) << left << BugAlive;
    } else if (this->type == "Hopper") {
        oss << setw(ColumnWidth) << left << std::to_string(this->getHopLength())
            << setw(statusColumnWidth) << left << BugAlive;
    } else if (this->type == "Scorpion") {
        oss << setw(ColumnWidth) << left << "-"
            << setw(statusColumnWidth) << left << BugAlive;
    }

// Output the final string with aligned columns
    std::cout << oss.str() << std::endl;
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


//void Bug::tap() {
//    if (!m_tapped) {
//        m_tapped = true;
//
//        // Call move() on all bugs
//        for (auto& bug : bugs) {
//            bug->move();
//        }
//
//        // Implement the fight/eat behavior
//        for (auto& bug : bugs) {
//          bug->eat(getSize());
//           }
//        }
//    }


void Bug::eat(int i) {
    // Check for bugs on the same cell
    for (size_t i = 0; i < bugs.size(); ++i) {
        for (size_t j = i + 1; j < bugs.size(); ++j) {
            if (bugs[i]->getPosition() == bugs[j]->getPosition()) {

                // Determine which bug eats the other
                if (bugs[i]->getSize() > bugs[j]->getSize()) {
                    bugs[i]->eat(bugs[j]->getSize());
                    bugs[j]->setAlive(false);
                } else if (bugs[i]->getSize() < bugs[j]->getSize()) {
                    bugs[j]->eat(bugs[i]->getSize());
                    bugs[i]->setAlive(false);
                } else {

                    // Randomly determine which bug eats the other
                    int winner = rand() % 2;
                    if (winner == 0) {
                        bugs[i]->eat(bugs[j]->getSize());
                        bugs[j]->setAlive(false);
                    } else {
                        bugs[j]->eat(bugs[i]->getSize());
                        bugs[i]->setAlive(false);
                    }
                }
            }
        }
    }
    // Remove dead bugs
    bugs.erase(remove_if(bugs.begin(), bugs.end(), [](Bug* bug) {
        return !bug->isAlive();
    }), bugs.end());
}



