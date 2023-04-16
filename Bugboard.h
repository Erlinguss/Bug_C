

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


    void findBug() const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayCells() const;
    void runSimulation(sf::RenderWindow& window);
    void writeLifeHistoryToFile();
    void eat();
    void BugData();
    void initializeBoard();
    void addBug(Bug* bug);
    vector<Bug*> getBoard();

    void initializeBoard(vector<Bug *> &bug_vector, BugBoard &board);

    void displayBugs() const;

protected:

    vector<Bug*> bugs;
    vector<Bug*> bug_vector;

   // void initializeBoard();



};

#endif
