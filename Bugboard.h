

#ifndef BUGBOARD_H
#define BUGBOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Scorpion.h"

using namespace std;

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

class BugBoard {

public:
    BugBoard();

    void findBug() const;

    void tapBoard();

    void displayLifeHistory() const;

    void displayCells() const;

    void runSimulation();

    void writeLifeHistoryToFile();

    void initializeBoard();

    void addBug(Bug *bug);

    vector<Bug *> getBoard();

    void displayBugs() const;

    void displayCells(int numSteps) const;

    void moveSuperBug(int x, int y);


protected:

    vector<Bug *> bugs;

    void header() const;

    void footer() const;

    void eat();


};

#endif
