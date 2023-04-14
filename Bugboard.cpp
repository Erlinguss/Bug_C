//
// Created by User on 15/03/2023.
//

#include "Bugboard.h"

using namespace std;

BugBoard::BugBoard() {
    initializeBoard();
}

void BugBoard::initializeBoard() {

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
        bool alive;
        Direction direction;

        iss >> bugType >> id >> x >> y  >> size >> hopLength >> alive;
        Bug* bug = nullptr;

        if (bugType == "Crawler") {
            bug = new Crawler(id, make_pair(x, y), direction, size,hopLength, alive);
        }
        else if (bugType == "Hopper") {
            bug = new Hopper(id, make_pair(x, y), direction,  size, hopLength, alive);
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


void BugBoard::displayBugs() const {
    cout << "ID\tType\t\tPosition\tDirection\tSize\t\tHop Length\tStatus" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (const Bug* bug : bugs) {
        string type = "";
        if (dynamic_cast<const Crawler*>(bug) != nullptr) {
            type = "Crawler";
        }
        else if (dynamic_cast<const Hopper*>(bug) != nullptr) {
            type = "Hopper";
        }

        string direction;
        switch (bug->getDirection()) {
            case Direction::NORTH:
                direction = "NORTH";
                break;
            case Direction::SOUTH:
                direction = "SOUTH";
                break;
            case Direction::EAST:
                direction = "EAST";
                break;
            case Direction::WEST:
                direction = "WEST";
                break;
            default:
                direction = "UNKNOWN";
                break;
        }

        cout << bug->getId() << "\t" << type
             << "\t\t(" << bug->getPosition().first << "," << bug->getPosition().second
             << ")\t\t"
             << direction // Use the string representation of direction
             << "\t\t\t" << bug->getSize()
             << "\t\t\t" << bug->getHopLength()
             << "\t\t\t" << bug->getStatus() << endl;
    }
}

void BugBoard::findBug() const {
    int id;
    cout << "Enter the ID of the bug you want to find: ";
    cin >> id;

    bool found = false;
    for (Bug* bug : bugs) {
        if (bug->getId() == id) {
            cout << "Bug ID: " << bug->getId() << endl;
            cout << "Position: (" << bug->getPosition().first << "," << bug->getPosition().second << ")" << endl;
           cout << "Direction: "  << static_cast<bool>(bug->getDirection()) << endl;
            cout << "Size: " << bug->getSize() << endl;
            cout << "HopLength : " << bug->getHopLength()<< endl;
            cout << "Status : " << bug->getStatus() << endl;

            if (dynamic_cast<Crawler*>(bug) != nullptr) {
                cout << "Bug type: Crawler" << endl;
            }
            else if (dynamic_cast<Hopper*>(bug) != nullptr) {
                cout << "Bug type: Hopper" << endl;
            }
            cout << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Bug with ID " << id << " not found." << endl;
    }
}

void BugBoard::tapBoard() {
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

    // Call move() function on all bugs
    for (Bug* bug : bugs) {
        bug->move();
    }
}


void BugBoard::displayLifeHistory() const {

    for (const auto bug : bugs) {
        string type = "";
        if (dynamic_cast<Crawler*>(bug) != nullptr) {
            type = "Crawler";
        }
        else if (dynamic_cast<Hopper*>(bug) != nullptr) {
            type = "Hopper";
        }
        cout << bug->getId() <<" " << type << " Path(life history) : ";
        const auto& path = bug->getPath();


        if (path.empty()) {
            cout << "No movements yet" << endl;
        } else {
            for (const auto& point : path) {
                cout << "(" << point.first << "," << point.second << ") ";
            }
            cout << endl;
        }
    }
}


void BugBoard::displayCells() const {

    cout << "Current Cells:" << endl;

    // Iterate over the board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // Check if there is a bug at this position
            bool found = false;
            for (Bug* bug : bugs) {
                if (bug->getPosition() == make_pair(x, y) && bug->isAlive()) {
                    found = true;
                    // Display bug's type and id
                    cout << "| " << bug->getType() << " " << bug->getId() << "  ";
                    break;
                }
            }

            // If a bug is not present, display empty cell
            if (!found) {
                cout << "| " << "    ";
            }
        }
        cout << "|" << endl;
    }
}

void BugBoard::runSimulation(sf::RenderWindow& window) {
    int numSteps;
    cout << "Enter the number of simulation steps: ";
    cin >> numSteps;

    // Run the simulation for the specified number of steps
    for (int i = 0; i < numSteps; i++) {
        for (auto bug : bugs) {
            if (bug->isAlive()) {
                // Move the bug
                bug->move();

//             Check for collision with other bugs
                for (auto other : bugs) {
                    if (bug != other && bug->getPosition() == other->getPosition() && other->isAlive()) {
                        bug->collide(other);
                    }
                }
            }
        }

        displayCells();
        sf::sleep(sf::seconds(0.1));
    }
    // Display the final positions of the bugs
    displayCells();
}


void BugBoard::writeLifeHistoryToFile() {
    ofstream file;
    file.open("bugs_life_history_date_time.out.txt");

    for (const auto bug: bugs) {
        string type = "";
        if (dynamic_cast<Crawler *>(bug) != nullptr) {
            type = "Crawler";
        } else if (dynamic_cast<Hopper *>(bug) != nullptr) {
            type = "Hopper";
        }

        for (const auto &bug: bugs) {
            file << "Bug ID: " << bug->getId() << "\n";
            file << "Bug Type: " << type << "\n";
        }

        file.close();
    }
}
void BugBoard::eat() {
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