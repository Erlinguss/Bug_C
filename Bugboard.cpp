//
// Created by User on 15/03/2023.
//

#include "Bugboard.h"

using namespace std;

BugBoard::BugBoard() {
  //  initializeBoard();
}

vector<Bug*> BugBoard::getBoard() {
    return bugs;
}

void BugBoard::addBug(Bug* bug) {
    bugs[bug->getPosition().first][bug->getPosition().second] = *bug;
}

void BugBoard::initializeBoard(vector<Bug*>& bug_vector, BugBoard& board) {

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
        istringstream iss(line);
        string bugType;
        int id, x, y, size, hopLength;
        bool alive;
        Direction direction;
        string temp;

        iss >> bugType >> id >> x >> y  >> size >> hopLength >> alive;

        getline(iss, temp, ';');
        if (!temp.empty()) {
            try {
                alive = stoi(temp); // Extract alive value
            } catch (const std::invalid_argument& e) {
                cerr << "Failed to convert alive value: " << temp << endl;
                continue; // Skip current line and move to next line
            }
        } else {
            // Set a default value for alive (e.g., true or false)
            alive = false; // or true, depending on your desired default value
        }

        Bug* bug = nullptr;

        if (bugType == "C") {
            getline(iss, temp, ';');
            id = stoi(temp);
            getline(iss, temp, ';');
            x = stoi(temp);
            getline(iss, temp, ';');
            y = stoi(temp);
            getline(iss, temp, ';');
            direction = static_cast<Direction>(stoi(temp));
            getline(iss, temp, ';');
            size = stoi(temp);

            Crawler* crawler = new Crawler(id, make_pair(x, y), direction, size, alive, list<pair<int, int>>());
            crawler->setType("Crawler");
            bug_vector.push_back(crawler);
            board.addBug(crawler);
        }
        else if (bugType == "H") {
            getline(iss, temp, ';');
            id = stoi(temp);
            getline(iss, temp, ';');
            x = stoi(temp);
            getline(iss, temp, ';');
            y = stoi(temp);
            getline(iss, temp, ';');
            direction = static_cast<Direction>(stoi(temp));
            getline(iss, temp, ';');
            size = stoi(temp);
            getline(iss, temp, ';');
            hopLength = stoi(temp);

            Hopper* hopper = new Hopper(id, make_pair(x, y), direction,  size, hopLength, alive, list<pair<int, int>>());
            hopper->setType("Hopper");
            bug_vector.push_back(hopper);
            board.addBug(hopper);

        }

//        if (bug != nullptr) {
//            bugs.push_back(bug);
//        }
    }
    inFile.close();
}
//
//void BugBoard::displayBugs(vector<Bug*>& bug_vector) {
//
//    for(int i = 0; i < bug_vector.size(); i++) {
//        if(bug_vector[i]->getType() == "Crawler") {
//            bug_vector[i]->BugData();
//        } else if(bug_vector[i]->getType() == "Hopper") {
//            bug_vector[i]->BugData();
//        }
//    }
//}

void BugBoard::displayBugs() const {
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "ID\tType\t\tPosition\tDirection\t\tSize\t\tHop Length\tStatus" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    for (const Bug* bug : bugs) {

        //bug->BugData();

        string type = "";
        if (dynamic_cast<const Crawler *>(bug) != nullptr) {
            type = "Crawler";
        } else if (dynamic_cast<const Hopper *>(bug) != nullptr) {
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
             << direction
             << "\t\t\t" << bug->getSize()
             << "\t\t\t" << bug->getHopLength()
             << "\t\t\t" << bug->isAlive() << endl;
    }

        cout << "--------------------------------------------------------------------------" << endl;
    }


void BugBoard::findBug() const {
    int id;
    cout << "Enter the ID of the bug you want to find: ";
    cin >> id;

    bool found = false;
    for (Bug* bug : bugs) {
        if (bug->getId() == id) {
            cout << "Bug ID: " << bug->getId() << endl;

            if (dynamic_cast<Crawler*>(bug) != nullptr) {
                cout << "Bug type: Crawler" << endl;
            }
            else if (dynamic_cast<Hopper*>(bug) != nullptr) {
                cout << "Bug type: Hopper" << endl;
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

            cout << "Position: (" << bug->getPosition().first << "," << bug->getPosition().second << ")" << endl;
            cout << "Direction: "  << direction << endl;
         //   cout << "Direction: "  << static_cast<bool>(bug->getDirection()) << endl;
            cout << "Size: " << bug->getSize() << endl;
            cout << "HopLength : " << bug->getHopLength()<< endl;
            cout << "Status : " << bug->isAlive() << endl;


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