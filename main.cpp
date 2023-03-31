#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
using namespace std;

const int CELL_SIZE = 50; // Size of each cell in pixels
const int BOARD_WIDTH = 10; // Width of the board in cells
const int BOARD_HEIGHT = 10; // Height of the board in cells

void initializeBoard(vector<Bug*>& bugs);
void displayBugs(const vector<Bug*>& bugs);
void findBug(const vector<Bug*>& bugs);
void tapBoard(vector<Bug*>& bugs);
void displayLifeHistory(const vector<Bug*>& bugs);
void displayCells(const vector<Bug*>& bugs);
void runSimulation(vector<Bug*>& bugs);

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_WIDTH, CELL_SIZE * BOARD_HEIGHT), "Bug Board");

    // Create the bugs vector
   vector<Bug*> bugs;

    // Initialize the bug board
    initializeBoard(bugs);

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for menu selections
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        initializeBoard(bugs);
                        break;
                    case sf::Keyboard::Num2:
                        displayBugs(bugs);
                        break;
                    case sf::Keyboard::Num3:
                        findBug(bugs);
                        break;
                    case sf::Keyboard::Num4:
                        tapBoard(bugs);
                        break;
                    case sf::Keyboard::Num5:
                        displayLifeHistory(bugs);
                        break;
                    case sf::Keyboard::Num6:
                        displayCells(bugs);
                        break;
                    case sf::Keyboard::Num7:
                        runSimulation(bugs);
                        break;
                    case sf::Keyboard::Num8:
                        // Write Life History of all Bugs to file
                        ofstream outFile("life_history.txt");
                        for (Bug* bug : bugs) {
                            outFile << bug->getId() << ": ";
                            for (auto& pos : bug->getPath()) {
                                outFile << "(" << pos.first << "," << pos.second << ") ";
                            }
                            outFile <<endl;
                        }
                        outFile.close();
                        break;
//                    default:
//                   break;
                }
            }
        }

        // Clear the screen
        // window.clear(sf::Color::White);
        //=================================================

        window.clear(sf::Color(127, 127, 127));

        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cellShape.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                cellShape.setFillColor(sf::Color::White);
                cellShape.setOutlineThickness(1);
                cellShape.setOutlineColor(sf::Color(192, 192, 192));
                window.draw(cellShape);
            }
        }
        //=================================================

        // Draw the bugs
//        for (Bug* bug : bugs) {
//            sf::RectangleShape bugShape(sf::Vector2f(CELL_SIZE * bug->getSize(), CELL_SIZE * bug->getSize()));
//            bugShape.setPosition(CELL_SIZE * bug->getPosition().first, CELL_SIZE * bug->getPosition().second);
//            bugShape.setFillColor(bug->getColor());
//            window.draw(bugShape);
//        }

        //=================================================
        for (Bug* bug : bugs) {
            sf::CircleShape bugShape(CELL_SIZE * bug->getSize() / 2);
            bugShape.setPosition(CELL_SIZE * bug->getPosition().first + CELL_SIZE / 2 - bugShape.getRadius(),
                                 CELL_SIZE * bug->getPosition().second + CELL_SIZE / 2 - bugShape.getRadius());
            bugShape.setFillColor(bug->getColor());
            window.draw(bugShape);
        }

       //=================================================
        // Display the window
        window.display();
    }

    // Delete the bugs
    for (Bug* bug : bugs) {
        delete bug;
    }

    return 0;
}

void initializeBoard(vector<Bug*>& bugs) {


    // Clear the bugs vector
    for (Bug* bug : bugs) {
        delete bug;
    }
    bugs.clear();

    // Load the bugs from file
   ifstream inFile("bugs.txt");
    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string bugType;
        int id, x, y, size, hopLength;
        float speed;
        int r, g, b;
        iss >> bugType >> id >> x >> y >> size >> hopLength >> speed >> r >> g >> b;
        Bug* bug = nullptr;

        if (bugType == "Crawler") {
            sf::Color color(r, g, b);
            bug = new Crawler(id, make_pair(x, y), size, color,hopLength, speed);
//            cerr << "Unable to open file bugs.txt" << endl;

        }
        else if (bugType == "Hopper") {
            sf::Color color(r, g, b);
            bug = new Hopper(id, make_pair(x, y), size, color, hopLength, speed);
//            cerr << "Unable to open file bugs.txt" << endl;

        }
        if (bug != nullptr) {
            bugs.push_back(bug);
        }
        else{
            cerr << "Unable to open file bugs.txt" << endl;
        }
    }
    inFile.close();
}


void displayBugs(const vector<Bug*>& bugs) {

    cout << "Bugs on the board:" << endl;
    for (Bug* bug : bugs) {
       cout << "ID: " << bug->getId() << ", Type: " << bug->getType() << ", Position: (" << bug->getPosition().first << "," << bug->getPosition().second << ")" << endl;
    }
}

void findBug(const vector<Bug*>& bugs) {
    int id;
    cout << "Enter the ID of the bug you want to find: ";
    cin >> id;
    Bug* bug = nullptr;
    for (Bug* b : bugs) {
        if (b->getId() == id) {
            bug = b;
            break;
        }
    }
    if (bug != nullptr) {
        cout << "Bug found: " << bug->getType() << " with ID " << bug->getId() << endl;
    }
    else {
        cout << "Bug not found." << endl;
    }
}

void tapBoard(vector<Bug*>& bugs) {
    int x, y;
    cout << "Enter the x and y coordinates of the cell you want to tap: ";
    cin >> x >> y;
    bool tapped = false;
    for (Bug* bug : bugs) {
        if (bug->getPosition() == make_pair(x, y)) {
            bug->tap();
            cout << "Bug tapped." << endl;
            tapped = true;
            break;
        }
    }
    if (!tapped) {
        cout << "No bug found at (" << x << "," << y << ")." << endl;
    }
}

void displayLifeHistory(const vector<Bug*>& bugs) {
    for (Bug* bug : bugs) {

        cout << "Bug " << bug->getId() << " life history:" << endl;
        for (auto& pos : bug->getPath()) {
            cout << "(" << pos.first << "," << pos.second << ") ";
        }
        cout << endl;
    }
}

void displayCells(const vector<Bug*>& bugs) {
    // Create a 2D vector of cells
   vector<vector<char>> cells(BOARD_HEIGHT, vector<char>(BOARD_WIDTH, '-'));

    // Fill in the cells with bug information
    for (Bug* bug : bugs) {
        int x = bug->getPosition().first;
        int y = bug->getPosition().second;
        char c;
        if (reinterpret_cast<const char *>(bug->getType()) == "Crawler") {
            c = 'C';
        }
        else {
            c = 'H';
        }
        cells[y][x] = c;
    }

    // Display the cells
    cout << "  ";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
       cout << y << " ";
        for (int x = 0; x < BOARD_WIDTH; x++) {
       cout << cells[y][x] << " ";
        }
       cout << endl;
    }
}

void runSimulation(vector<Bug*>& bugs) {
    int numSteps;
    cout << "Enter the number of simulation steps: ";
    cin >> numSteps;

    // Run the simulation for the specified number of steps
    for (int i = 0; i < numSteps; i++) {
        for (Bug* bug : bugs) {
            // Move the bug
            bug->move();

            // Check for collision with other bugs
            for (Bug* other : bugs) {
                if (bug != other && bug->getPosition() == other->getPosition()) {
                    bug->collide(other);
                }
            }
        }
    }

    // Display the final positions of the bugs
    displayCells(bugs);
}



