

#ifndef CRAWLER_H
#define CRAWLER_H


#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Bug.h"
using namespace std;

class BugBoard {

public:
    BugBoard();

    void loadBugsFromFile(const std::string& filename);
    void displayAllBugs() const;
    shared_ptr<Bug> findBug(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayAllCells() const;
    void runSimulation(sf::RenderWindow& window);
    //void runSimulation(sf::RenderWindow);


private:
    vector<vector<shared_ptr<Bug>>> board_;
    vector<shared_ptr<Bug>> allBugs_;
    vector<shared_ptr<Bug>> aliveBugs_;
    int numAliveBugs_;

    void initializeBoard();
    void moveBugs();
    void checkCollisions();
    void eatBug(shared_ptr<Bug> winner, shared_ptr<Bug> loser);
};

#endif // CRAWLER_H
