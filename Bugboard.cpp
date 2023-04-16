//
// Created by User on 15/03/2023.
//

#include "Bugboard.h"
#include <iomanip>

using namespace std;

const int CELL_SIZE = 50; // Size of each cell in pixels

BugBoard::BugBoard() {

}

void BugBoard::initializeBoard() {

    // Clear the bugs vector
    for (Bug* bug : bugs) {
        delete bug;
    }
    bugs.clear();

    // Load the bugs from file
    ifstream inFile("bugs.txt");
    if (!inFile.is_open()) {
        cerr << "Unable to open file bugs.txt" << endl;
        return; // Return early if file cannot be opened
    }
    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        string bugType;
        int id, x, y, size, hopLength;
        bool alive;
        Direction direction;
        string temp;

        getline(ss, bugType, ';');
        //ss>>id >> x >> y  >> size >> hopLength >> alive;


        // Set a default value for alive (e.g., true or false)
        alive = false; // or true, depending on desired default value

        if (bugType == "C") {
            getline(ss, temp, ';');
            id = stoi(temp);
            getline(ss, temp, ';');
            x = stoi(temp);
            getline(ss, temp, ';');
            y = stoi(temp);
            getline(ss, temp, ';');
            direction = static_cast<Direction>(stoi(temp));
            getline(ss, temp, ';');
            size = stoi(temp);

            Crawler* crawler = new Crawler(id, make_pair(x, y), direction, size, alive, list<pair<int, int>>());
            crawler->setType("Crawler");
            bugs.push_back(crawler);
        }
        else if (bugType == "H") {
            getline(ss, temp, ';');
            id = stoi(temp);
            getline(ss, temp, ';');
            x = stoi(temp);
            getline(ss, temp, ';');
            y = stoi(temp);
            getline(ss, temp, ';');
            direction = static_cast<Direction>(stoi(temp));
            getline(ss, temp, ';');
            size = stoi(temp);
            getline(ss, temp, ';');
            hopLength = stoi(temp);
            Hopper* hopper = new Hopper(id, make_pair(x, y), direction,  size, alive, list<pair<int, int>>(),  hopLength);
            hopper->setType("Hopper");
            bugs.push_back(hopper);
        }
    }
    inFile.close();
}

void BugBoard:: header() const{
    cout << " "<< endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "ID\tType\t\tPosition\tDirection\t\tSize\t\tHop Length\tStatus" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

}

void BugBoard:: footer() const{
      cout << "--------------------------------------------------------------------------" << endl;
      cout << " "<< endl;

}

void BugBoard::displayBugs() const {
   header();
    for ( Bug *bug : bugs) {
        bug->BugData();
    }
   footer();
}


void BugBoard::findBug() const {
    int id;
    cout << "Enter the ID of the bug you want to find: ";
    cin >> id;
    bool found = false;

    header();
    for (Bug *bug : bugs) {
        if (bug->getId() == id) {
            found = true;
            bug->BugData();
            break;
        }
    }
    footer();

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

    // Set the width of each cell to a fixed size
    int cellWidth = 5;
    int cellWidth1 = 3;

    // Iterate over the board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // Check if there is a bug at this position
            bool found = false;
            for (Bug* bug : bugs) {
                  if (bug->getPosition() == make_pair(x, y) && bug->isAlive()) {
               // if (bug->getPosition() == make_pair(x, y)) {
                    found = true;
                    // Display bug's type and id
                    cout << "|" <<"(" << x << "," << y << "):" << bug->getType() << " " << bug->getId() << setw(cellWidth1)<< left;
                    break;
                }
            }
            // If a bug is not present, display position and "empty"
            if (!found) {
                cout << "|"  << "(" << x << "," << y << "): empty   "<< setw(cellWidth); // Display position and "empty"
            }
        }
        cout << "|" << endl;
    }
}
//
//void BugBoard::displayCells() const {
//
//    for (int x = 0; x <= BOARD_WIDTH; ++x) {
//        for (int y = 0; y <= BOARD_HEIGHT; ++y) {
//            string cell_status = "";
//            for (const Bug* bug : bugs) {
//                if (bug->getPosition() == make_pair(x, y) && bug->isAlive()) {
//                    if (!cell_status.empty()) {
//                        cell_status += ", ";
//                    }
//                    cell_status += bug->getType() + " " + to_string(bug->getId());
//                }
//            }
//            if (cell_status.empty()) {
//                cell_status = "empty";
//            }
//            cout << "(" << x << "," << y << "): " << cell_status << endl;
//        }
//    }
//}

//void BugBoard::runSimulation(sf::RenderWindow& window) {
//    int numSteps;
//    cout << "Enter the number of simulation steps: ";
//    cin >> numSteps;
//
//    // Run the simulation for the specified number of steps
//    for (int i = 0; i < numSteps; i++) {
//        for (auto bug : bugs) {
//            if (bug->isAlive()) {
//                // Move the bug
//                bug->move();
//
//             Check for collision with other bugs
//                for (const auto other : bugs) {
//                    if (bug != other && bug->getPosition() == other->getPosition() && other->isAlive()) {
//
//                        bug->collide(other);
//                    }
//                }
//            }
//        }
//
//        displayCells( );
//        sf::sleep(sf::seconds(0.1));
//    }
//
//}

void BugBoard::runSimulation(sf::RenderWindow& window) {
    int numSteps;
    cout << "Enter the number of simulation steps: ";
    cin >> numSteps;

    int numAliveBugs = 0; // Track the number of alive bugs

    // Run the simulation for the specified number of steps
    for (int i = 0; i < numSteps; i++) {
        // Move bugs and check for collisions
        for (auto bug : bugs) {
            if (bug->isAlive()) {
                // Move the bug
                bug->move();

                // Check for collision with other bugs
                for (const auto other : bugs) {
                    if (bug != other && bug->getPosition() == other->getPosition() && other->isAlive()) {
                        bug->collide(other);
                    }
                }

                // Check for collision with neighboring bugs
                for (auto other : bugs) {
                    if (bug != other && bug->isAlive() && other->isAlive()) {
                        if (abs(bug->getPosition().first - other->getPosition().first) <= 1 &&
                            abs(bug->getPosition().second - other->getPosition().second) <= 1) {
                            bug->collide(other);
                        }
                    }
                }
            }
        }

        displayCells();
        sf::sleep(sf::seconds(0.1));

        // Update the number of alive bugs after each simulation step
        numAliveBugs = 0;
        for (const auto bug : bugs) {
            if (bug->isAlive()) {
                numAliveBugs++;
            }
        }

        // Check if only one bug is alive and exit the simulation if true
        if (numAliveBugs == 1) {
            cout << "Game Over!" << endl;
            return;
        }
    }

    cout << "Game Over!" << endl;
}


void BugBoard::writeLifeHistoryToFile() {
    ofstream file;
    file.open("bugs_life_history_date_time.out.txt");


        for (const auto &bug: bugs) {
                string type = "";
                if (dynamic_cast<Crawler *>(bug) != nullptr) {
                    type = "Crawler";
                } else if (dynamic_cast<Hopper *>(bug) != nullptr) {
                    type = "Hopper";
                }
            file << "Bug ID: " << bug->getId() << "\n";
            file << "Bug Type: " << type << "\n";
        }

        file.close();
    }

//
//void BugBoard::eat() {
//    // Check for bugs on the same cell
//    for (size_t i = 0; i < bugs.size(); ++i) {
//        for (size_t j = i + 1; j < bugs.size(); ++j) {
//            if (bugs[i]->getPosition() == bugs[j]->getPosition()) {
//                // Determine which bug eats the other
//                if (bugs[i]->getSize() > bugs[j]->getSize()) {
//                    bugs[i]->eat(bugs[j]->getSize());
//                    bugs[j]->setAlive(false);
//                } else if (bugs[i]->getSize() < bugs[j]->getSize()) {
//                    bugs[j]->eat(bugs[i]->getSize());
//                    bugs[i]->setAlive(false);
//                } else {
//                    // Randomly determine which bug eats the other
//                    int winner = rand() % 2;
//                    if (winner == 0) {
//                        bugs[i]->eat(bugs[j]->getSize());
//                        bugs[j]->setAlive(false);
//                    } else {
//                        bugs[j]->eat(bugs[i]->getSize());
//                        bugs[i]->setAlive(false);
//                    }
//                }
//            }
//        }
//    }
//    // Remove dead bugs
//    bugs.erase(remove_if(bugs.begin(), bugs.end(), [](Bug* bug) {
//        return !bug->isAlive();
//    }), bugs.end());
//}