////
//// Created by User on 10/04/2023.
////
//
//
//#include "SuperBug.h"
//using namespace std;
//
//SuperBug::SuperBug(int id, int x, int y) : Bug(id, x,  y, direction,  size) {
//    // Constructor implementation for SuperBug
//}
//
//void SuperBug::move() {
//    // Get the current position of the SuperBug
//    int currentX = getPosition().first;
//    int currentY = getPosition().second;
//
//    // Calculate the new position by moving diagonally
//    int newX = currentX + 1;
//    int newY = currentY + 1;
//
//    // Update the position of the SuperBug
//    setPosition(make_pair(newX, newY));
//
//    // Print a message to indicate the move
//    cout << "SuperBug with ID " << getId() << " moved to (" << newX << ", " << newY << ")." << endl;
//}