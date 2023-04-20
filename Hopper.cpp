
#include <iomanip>
#include <sstream>
#include "Hopper.h"

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

Hopper::Hopper(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path,
               int hopLength)
        : Bug(id, position.first, position.second, direction, size, alive, path), hopLength(hopLength) {
    this->m_color = sf::Color::Red;
}

int Hopper::getHopLength() const {
    return this->hopLength;
}

void Hopper::setHopLength(int hopLength) {
    this->hopLength = hopLength;
}


/*=======================================================
             METHOD TO MOVE THE HOPPER
========================================================*/
void Hopper::move() {

    while (this->isWayBlocked()) {
        setRandomDirection();
    }
    pair<int, int> Direction_X_Y = getDirection();
    int directionX = Direction_X_Y.first;
    int directionY = Direction_X_Y.second;
    int newDirectionX = position.first + directionX * hopLength;
    int newDirectionY = position.second + directionY * hopLength;
    if (newDirectionX > 9) {
        newDirectionX = 9;
    } else if (newDirectionX < 0) {
        newDirectionX = 0;
    }
    if (newDirectionY > 9) {
        newDirectionY = 9;
    } else if (newDirectionY < 0) {
        newDirectionY = 0;
    }
    setPosition(make_pair(newDirectionX, newDirectionY));
    addToPath(getPosition());

}

/*=======================================================
          METHOD TO SET A RANDOM DIRECTION
========================================================*/
void Hopper::setRandomDirection() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 3);
    int randInt = dis(gen);
    direction = static_cast<Direction>(randInt);
}

/*=======================================================
          METHOD TO SET A RANDOM DIRECTION
========================================================*/
const pair<int, int> Hopper::getDirection() const {
    int hopperX = 0, hopperY = 0;
    switch (direction) {
        case Direction::NORTH:
            hopperY = -1;
            break;
        case Direction::EAST:
            hopperX = 1;
            break;
        case Direction::SOUTH:
            hopperY = 1;
            break;
        case Direction::WEST:
            hopperX = -1;
            break;
    }
    return make_pair(hopperX, hopperY);
}

/*=======================================================
        DISPLAY THE DATA FROM EACH BUG & HOPPER
========================================================*/
void Hopper::BugData() {

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

    int idColumnWidth = 4;
    int typeColumnWidth = 12;
    int positionColumnWidth = 12;
    int directionColumnWidth = 16;
    int sizeColumnWidth = 12;
    int ColumnWidth = 13;
    int statusColumnWidth = 10;


    std::ostringstream oss;
    oss << setw(idColumnWidth) << left << std::to_string(this->getId())
        << setw(typeColumnWidth) << left << type
        << setw(positionColumnWidth) << left << "(" + std::to_string(this->getPosition().first) + "," +
                                                std::to_string(this->getPosition().second) + ")"
        << setw(directionColumnWidth) << left << BugDirection
        << setw(sizeColumnWidth) << left << std::to_string(this->getSize());

    if (this->type == "Crawler") {
        oss << setw(ColumnWidth) << left << "-"
            << setw(statusColumnWidth) << left << BugAlive;
    } else if (this->type == "Hopper") {
        oss << setw(ColumnWidth) << left << std::to_string(this->getHopLength())
            << setw(statusColumnWidth) << left << BugAlive;
    } else if (this->type == "Scorpion") {
        oss << setw(ColumnWidth) << left << "-"
            << setw(statusColumnWidth) << left << BugAlive;
    } else if (this->type == "SuperBug") {
        oss << setw(ColumnWidth) << left << "-"
            << setw(statusColumnWidth) << left << BugAlive;
    }

    cout << oss.str() << endl;

}