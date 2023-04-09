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
        float speed;
        iss >> bugType >> id >> x >> y >> size >> hopLength >> speed;
        Bug* bug = nullptr;

        if (bugType == "Crawler") {
            bug = new Crawler(id, make_pair(x, y), size,hopLength, speed);
        }
        else if (bugType == "Hopper") {
            bug = new Hopper(id, make_pair(x, y), size, hopLength, speed);
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
    cout << "ID\tType\t\tPosition\tSize\tColor" << endl;
    cout << "--------------------------------------------------" << endl;
    for (Bug* bug : bugs) {
        string type = "";
        if (dynamic_cast<Crawler*>(bug) != nullptr) {
            type = "Crawler";
        }
        else if (dynamic_cast<Hopper*>(bug) != nullptr) {
            type = "Hopper";
        }
        cout << bug->getId() << "\t" << type
             << "\t\t(" << bug->getPosition().first
             << "," << bug->getPosition().second
             << ")\t" << bug->getSize()
             << "\t\t(" << bug->getColor().r
             << "," << bug->getColor().g
             << "," << bug->getColor().b << ")" << endl;
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
            cout << "Size: " << bug->getSize() << endl;
            cout << "Color: (" << bug->getColor().r << "," << bug->getColor().g << "," << bug->getColor().b << ")" << endl;
            if (dynamic_cast<Crawler*>(bug)) {
                cout << "Bug type: Crawler" << endl;
            }
            else if (dynamic_cast<Hopper*>(bug)) {
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
}


void BugBoard::displayLifeHistory() const {
    for (const auto bug : bugs) {
        cout << "Bug " << bug->getId() << " life history: ";
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
    // Clear the screen
    // system("cls");
    cout << "Current Cells:" << endl;

    // Iterate over the board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // Check if there is a bug at this position
            bool found = false;
            for (Bug* bug : bugs) {
                if (bug->getPosition() == make_pair(x, y) && bug->isAlive()) {
                    found = true;
                    break;
                }
            }

            // If a bug is present, display its ID
            if (found) {
                cout << "| " << "BUG" << " ";
            } else {
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


void writeLifeHistoryToFile(const vector<Bug*>& bugs, const string& filename) {
    ofstream file;
    file.open("life_history.txt");

    for (const auto& bug : bugs) {
        file << "Bug ID: " << bug->getId() << "\n";
        file << "Bug Type: " << bug->getType()<< "\n";
    }

    file.close();
}