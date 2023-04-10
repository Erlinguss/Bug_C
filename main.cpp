#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Bugboard.h"
using namespace std;

const int CELL_SIZE = 50; // Size of each cell in pixels


void initializeBoard(vector<Bug*>& bugs);
void displayBugs(const vector<Bug*>& bugs);
void findBug(const vector<Bug*>& bugs);
void tapBoard(vector<Bug*>& bugs);
void displayLifeHistory(const vector<Bug*>& bugs);
void displayCells(const vector<Bug*>& bugs);
void runSimulation(vector<Bug*>& bugs);
void writeLifeHistoryToFile(const vector<Bug*>& bugs);

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_WIDTH, CELL_SIZE * BOARD_HEIGHT), "Bug Board");

    // Create the bugs vector
    vector<Bug *> bugs;


    // Initialize the bug board
    BugBoard board;

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
                        board.displayBugs();
                        break;
                    case sf::Keyboard::Num2:
                        board.findBug();
                        break;
                    case sf::Keyboard::Num3:
                        board.tapBoard();
                        break;
                    case sf::Keyboard::Num4:
                        board.runSimulation(window);
                        break;
                    case sf::Keyboard::Num5:
                        board.displayLifeHistory();
                        break;
                    case sf::Keyboard::Num6:
                        board.displayCells();
                        break;
                    case sf::Keyboard::Num7:
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
            //=================================================
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
            for (Bug *bug: bugs) {
                sf::CircleShape bugShape(bug->getSize() / 2);
                bugShape.setPosition(bug->getPosition().first + CELL_SIZE / 2 - bugShape.getRadius(),
                                     bug->getPosition().second + CELL_SIZE / 2 - bugShape.getRadius());
                bugShape.setFillColor(bug->getColor());
                window.draw(bugShape);
            }

            //=================================================
            // Display the window
            window.display();
        }

        // Delete the bugs
        for (Bug *bug: bugs) {
            delete bug;
        }

        return 0;
    }

