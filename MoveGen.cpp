//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * IMPLEMENTATION FILE FOR A MOVE GENERATOR
//============================================================================//

// INCLUDES
//============================================================================//
#include "MoveGen.h"
//============================================================================//

// CONSTRUCTORS
//============================================================================//
MoveGen::MoveGen() {
    inputBoardPosition = "xxxxxxxxxxxxxxxxxxxxxxx";
    copyBoardPosition = "";
}

MoveGen::MoveGen(std::string inputBoardPosition) {
    this->inputBoardPosition = inputBoardPosition;
    copyBoardPosition = "";
}
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
std::vector<std::string> MoveGen::generateAdd() {

    // BOARD POSITIONS MUST BE EMPTY
    //------------------------------------------------------------------------//
    boardPositions.clear();

    // GENERATE A LIST OF ALL POSSIBLE MOVES FOR W TO ANY OPEN SQUARE
    //------------------------------------------------------------------------//
    for (int i = 0; i < inputBoardPosition.length(); ++i) {
        if (inputBoardPosition[i] == 'x') {
            copyBoardPosition = inputBoardPosition;
            copyBoardPosition[i] = 'W';
            if (closeMill(i)) {
                generateRemove();
            } else {
                boardPositions.push_back(copyBoardPosition);
            }
        }
    }
    //------------------------------------------------------------------------//

    // RESET THE COPY FOR USE IN OTHER FUNCTIONS AND RETURN THE FUNCTION RESULT
    //------------------------------------------------------------------------//
    copyBoardPosition = "";
    return boardPositions;
} // generateAdd()

std::vector<std::string> MoveGen::generateMove() {

    // BOARD POSITIONS MUST BE EMPTY
    //------------------------------------------------------------------------//    
    boardPositions.clear();
    for (int i = 0; i < inputBoardPosition.length(); ++i) {
        if (inputBoardPosition[i] == 'W') {

        } 
    }
    return boardPositions;
}

int* MoveGen::neighbors(int& l) {

    // N WILL EITHER HAVE 3 OR 4 NEIGHBORS. n[0] IS N SIZE
    //------------------------------------------------------------------------//
    int numOfNeighbors = (l == 9 || l == 18 || l == 12) ? 5 : 4;
    int* n = new int[numOfNeighbors];
    n[0] = numOfNeighbors;
    for (int i = 1; i < n[0]; ++i)
        *(n + i) = -1;
    //------------------------------------------------------------------------//

    // FILL N WITH L'S NEIGHBORS
    //------------------------------------------------------------------------//
    switch (l) {
        case 0:
            *(n + 1) = 8;
            *(n + 2) = 3;
            *(n + 3) = 1;
            break;
        case 1:  
            *(n + 1) = 0;
            *(n + 2) = 4;
            *(n + 3) = 2;
            break;
        case 2:  
            *(n + 1) = 1;
            *(n + 2) = 5;
            *(n + 3) = 13;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        default: break;
    }
    //------------------------------------------------------------------------//
    return n;
}

void MoveGen::generateRemove() {
    bool nothingAddedToBoard = true;
    std::string localBoardCopy = copyBoardPosition;
    for (int i = 0; i < localBoardCopy.length(); ++i) {
        if (localBoardCopy[i] == 'B') {
            if (!closeMill(i)) {
                copyBoardPosition = localBoardCopy;
                copyBoardPosition[i] = 'x';
                boardPositions.push_back(copyBoardPosition);
                nothingAddedToBoard = false;
            }
        }
    }
    if (nothingAddedToBoard) {
        for (int i = 0; i < localBoardCopy.length(); ++i) {
            if (localBoardCopy[i] == 'B') {
                copyBoardPosition = localBoardCopy;
                copyBoardPosition[i] = 'x';
                boardPositions.push_back(copyBoardPosition);
            }
        }
    }
}
//============================================================================//

// GETTERS AND SETTERS
//============================================================================//
std::vector<std::string> MoveGen::getBoardPositions() {
    return boardPositions;
}

std::string MoveGen::getInputBoardPosition() {
    return inputBoardPosition;
}

std::string MoveGen::getCopyBoardPosition() {
    return copyBoardPosition;
}

void MoveGen::setBoardPositions(std::vector<std::string> boardPositions) {
    this->boardPositions = boardPositions;
}

void MoveGen::setInputBoardPosition(std::string inputBoardPosition) {
    this->inputBoardPosition = inputBoardPosition;
}

void MoveGen::setCopyBoardPosition(std::string copyBoardPosition) {
    this->copyBoardPosition = copyBoardPosition;
}
//============================================================================//