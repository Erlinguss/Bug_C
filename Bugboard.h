

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
using namespace std;

const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

class BugBoard {

public:
    BugBoard();

    void displayBugs() const;
    void findBug() const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayCells() const;
    void runSimulation(sf::RenderWindow& window);



private:
    vector<vector<Bug*>> board_;
    vector<Bug*> bugs;
    vector<Bug*> aliveBugs_;
    int numAliveBugs_;

    void initializeBoard();
};

#endif
