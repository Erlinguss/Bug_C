
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "Bugboard.h"

using namespace std;

const int CELL_SIZE = 50; // Size of each cell in pixels

void gui(BugBoard &board);

int main() {

    // Create the bugs vector
    vector<Bug *> bug_vector;


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
        cout << ">" << endl;


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
                cout << "Bugs were tapped" << endl;
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
                gui(board);
                cout << endl;
                break;
            case 8:
                board.writeLifeHistoryToFile();
                cout << "Data was saved in the file" << endl;
                break;
            case 9:
                cout << endl;
                cout << "End of the program." << endl;
                return 0;
                break;
            default:
                cout << endl;
                cout << "Invalid option" << endl;
                cout << endl;
        }
    }

    for (Bug *bug: bug_vector) {
        delete bug;
    }
    return 0;
}


void gui(BugBoard &board) {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_WIDTH, CELL_SIZE * BOARD_HEIGHT), "Bug Board");
    sf::Time time1;
    sf::Clock clock;

    // Load the bug texture
    sf::Texture bugTexture;
    if (!bugTexture.loadFromFile("images2.png")) {
        cerr << "Failed to load bug texture." << endl;
        return;
    }

    // Load the image texture
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("images2.png")) {
        cerr << "Failed to load image texture." << endl;
        return;
    }

    // Create a sprite for the image
    sf::Sprite imageSprite(imageTexture);

    // Scale the sprite to the size of a cell
    imageSprite.setScale(CELL_SIZE / imageSprite.getLocalBounds().width,
                         CELL_SIZE / imageSprite.getLocalBounds().height);

    // Set the origin of the sprite to its center
    imageSprite.setOrigin(imageSprite.getLocalBounds().width / 2,
                          imageSprite.getLocalBounds().height / 2);

    // Set the position of the sprite to the center of the cell
    imageSprite.setPosition(CELL_SIZE / 2, CELL_SIZE / 2);


    time1 = clock.getElapsedTime();
    bool runSimulation = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                board.tapBoard();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                cout << "Simulation started." << endl;
                runSimulation = !runSimulation;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                board.moveSuperBug(0, -1);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                board.moveSuperBug(-1, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                board.moveSuperBug(0, 1);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                board.moveSuperBug(1, 0);
            }
        }

        // Redraw the window after each menu option is executed
        window.clear(sf::Color(127, 127, 127));

        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cellShape.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                cellShape.setFillColor(sf::Color::White);
                cellShape.setOutlineThickness(1);
                cellShape.setOutlineColor(sf::Color(192, 192, 192));
                window.draw(cellShape);

                // Get the position of the current cell's center
                sf::Vector2f cellCenter((x + 0.5f) * CELL_SIZE, (y + 0.5f) * CELL_SIZE);

                // Set the position of the image sprite to the center of the current cell
                imageSprite.setPosition(cellCenter);

                // Check if the simulation is running
                if (runSimulation) {
                    // Get the time difference between now and the last tap
                    float diff = clock.getElapsedTime().asSeconds() - time1.asSeconds();

                    if (diff >= 0.5) {
                        board.tapBoard();
                        time1 = clock.getElapsedTime();
                    }

                    // Check how many bugs are still alive
                    int c = 0;
                    for (Bug *bug: board.getBoard()) {
                        if (bug->isAlive()) {
                            c++;
                        }
                    }
                    // If only one bug is left, stop the simulation
                    if (c == 1) {
                        runSimulation = false;
                    }
                }
            }
        }

        // Loop through all the bugs on the board
        for (Bug *bug: board.getBoard()) {

            // Check if the bug is in the current cell
            float s = (bug->getSize() * 4 > 100 ? 100.f : (float) bug->getSize() * 4);
            imageSprite.setScale(sf::Vector2f(s / imageTexture.getSize().x, s / imageTexture.getSize().y));
            imageSprite.setPosition(sf::Vector2f((bug->getPosition().first + 0.4f) * CELL_SIZE,
                                                 (bug->getPosition().second + 0.4f) * CELL_SIZE));
            window.draw(imageSprite);

            if (!bug->isAlive()) {
                imageSprite.setColor(sf::Color::Black);
            } else if (bug->getType() == "Crawler") {
                imageSprite.setColor(sf::Color::Green);
            } else if (bug->getType() == "Hopper") {
                imageSprite.setColor(sf::Color::Red);
            } else if (bug->getType() == "SuperBug") {
                imageSprite.setColor(sf::Color::Blue);
            } else {
                imageSprite.setColor(sf::Color::Yellow);
            }

            // Draw the image sprite on the window
            window.draw(imageSprite);
        }

        // Display the updated window
        window.display();

    }
}













