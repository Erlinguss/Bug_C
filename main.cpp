
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "Bugboard.h"


using namespace std;

const int CELL_SIZE = 50; // Size of each cell in pixels
int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_WIDTH, CELL_SIZE * BOARD_HEIGHT), "Bug Board");

    // Create the bugs vector
    vector<Bug*> bug_vector;


    // Initialize the bug board
    BugBoard board;


    int choice;
    while (true) {
        // Display the menu
        cout << endl;
        cout << "╔══════════════════════════════════╗" << endl;
        cout << "║            Bug Game Menu         ║" << endl;
        cout << "╠══════════════════════════════════╣" << endl;
        cout << "║ 1. Load file                     ║" << endl;
        cout << "║ 2. Display bugs                  ║" << endl;
        cout << "║ 3. Find bug                      ║" << endl;
        cout << "║ 4. Tap board                     ║" << endl;
        cout << "║ 5. Display life history          ║" << endl;
        cout << "║ 6. Display cells                 ║" << endl;
        cout << "║ 7. Run simulation                ║" << endl;
        cout << "║ 8. Write life history to file    ║" << endl;
        cout << "║ 9. Exit the program              ║" << endl;
        cout << "╠══════════════════════════════════╣" << endl;
        cout << "║ Enter your choice (1-9):         ║" << endl;
        cout << "╚══════════════════════════════════╝" << endl;


        try {
            if (!(cin >> choice)) {
                throw runtime_error("Invalid input. Please enter a numeric value.");
            }
        } catch (runtime_error &e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1:
                board.initializeBoard();
                cout << "File loaded" << endl;
                cout << endl;
                break;
            case 2:
                board.displayBugs();
                cout << endl;
                break;
            case 3:
                board.findBug();
                cout << endl;
                break;
            case 4:
                board.tapBoard();
                cout << endl;
                break;
            case 5:
                board.displayLifeHistory();
                cout << endl;
                break;
            case 6:
                board.displayCells();
                cout << endl;
                break;
            case 7:
                board.runSimulation(window);
                cout << endl;
                break;
            case 8:
                // Write Life History of all Bugs to file
                board.writeLifeHistoryToFile();
                cout << "Data was saved in the file" << endl;
                break;
            case 9:
                cout << endl;
                cout << "End of the program." << endl;
                //return 0;
            default:
                cout << endl;
                cout << "Invalid option" << endl;
                cout << endl;
        }

        // Redraw the window after each menu option is executed
        window.clear(sf::Color(127, 127, 127));

        // Draw cells and bugs on the window
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


        for (Bug *bug: bug_vector) {
            sf::CircleShape bugShape(bug->getSize() / 2);
            bugShape.setPosition(bug->getPosition().first + CELL_SIZE / 2 - bugShape.getRadius(),
                                 bug->getPosition().second + CELL_SIZE / 2 - bugShape.getRadius());
            bugShape.setFillColor(bug->getColor());
            window.draw(bugShape);
        }

        window.display();


        // Delete the bugs
        for (Bug *bug: bug_vector) {
            delete bug;
        }


    }
    return 0;
}