//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * IMPLEMENTATION FILE FOR A MOVE GENERATOR
//============================================================================//

// INCLUDES
//============================================================================//
#include "MoveGen.h"
#include <algorithm>
//============================================================================//

// CONSTRUCTORS
//============================================================================//
MoveGen::MoveGen() {
    inputBoardState = "xxxxxxxxxxxxxxxxxxxxxxx";
    copyBoardState = "";
}

MoveGen::MoveGen(std::string inputBoardState) {
    this->inputBoardState = inputBoardState;
    copyBoardState = "";
}
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
std::vector<std::string> MoveGen::generate_add() {

    // BOARD STATES MUST BE EMPTY
    //------------------------------------------------------------------------//
    boardStates.clear();

    // GENERATE A LIST OF ALL POSSIBLE MOVES FOR W TO ANY OPEN SQUARE
    //------------------------------------------------------------------------//
    for (int i = 0; i < inputBoardState.length(); ++i) {
        if (inputBoardState[i] == 'x') {
            copyBoardState = inputBoardState;
            copyBoardState[i] = 'W';
            if (close_mill(i)) {
                generate_remove();
            } else {
                boardStates.push_back(copyBoardState);
            }
        }
    }
    //------------------------------------------------------------------------//

    // RESET THE COPY FOR USE IN OTHER FUNCTIONS AND RETURN THE FUNCTION RESULT
    //------------------------------------------------------------------------//
    copyBoardState = "";
    return boardStates;
} // generate_add()

std::vector<std::string> MoveGen::generate_move() {

    // BOARD STATES MUST BE EMPTY
    //------------------------------------------------------------------------//    
    boardStates.clear();

    // LOOK THROUGH EVERY SQUARE ON THE BOARD
    //------------------------------------------------------------------------//
    for (int i = 0; i < inputBoardState.length(); ++i) {
        if (inputBoardState[i] == 'W') {
            
            // GET ALL THE NEIGHBORS FOR BOARD STATE AT i
            //----------------------------------------------------------------//
            int* n = neighbors(i);

            // n[0] = n SIZE; LOOP THROUGH ALL NEIGHBORS OF SQUARE AT i
            //----------------------------------------------------------------//
            for (int j = 1; j < *n; ++j) {

                // IF THE NEIGHBORING SQUARE AT n[j] IS EMPTY
                //------------------------------------------------------------//
                if (inputBoardState[*(n + j)] == 'x') {
                    copyBoardState = inputBoardState;
                    copyBoardState[i] = 'x';
                    copyBoardState[*(n + j)] = 'W';
                    if (close_mill(*(n + j))) {
                        generate_remove();
                    } else {
                        boardStates.push_back(copyBoardState);
                    }
                }
            }
            // DEALLOCATE RESOURCES
            //----------------------------------------------------------------//
            delete n;
        } 
    }
    // RESET THE COPY FOR USE IN OTHER FUNCTIONS AND RETURN THE FUNCTION RESULT
    //------------------------------------------------------------------------//
    copyBoardState = "";
    return boardStates;
} // generate_move()

std::vector<std::string> MoveGen::generate_moves_opening() {

    // CLASS MEMBER MANAGEMENT RENDERED THIS FUNCTION REDUNDANT
    //------------------------------------------------------------------------//
    return generate_add();
} // generate_moves_opening()

std::vector<std::string> MoveGen::generate_moves_midgame_endgame() {
    
    // IF THERE ARE 3 WHITE PIECES ON THE BOARD
    //------------------------------------------------------------------------//
    if (std::count(inputBoardState.begin(), inputBoardState.end(), 'W') == 3) {
        return generate_hopping();
    } else {
        return generate_move();
    }
} // generate_moves_midgame_endgame()

std::vector<std::string> MoveGen::generate_hopping() {
    
    // BOARD STATES MUST BE EMPTY
    //------------------------------------------------------------------------// 
    boardStates.clear();

    // FOR EVERY LOCATION ON THE CURRENT BOARD STATE
    //------------------------------------------------------------------------//
    for (int i = 0; i < inputBoardState.length(); ++i) {
        if (inputBoardState[i] == 'W') {

            // FOR EVERY LOCATION j ON THE CURRENT BOARD STATE
            //----------------------------------------------------------------//
            for (int j = 0; j < inputBoardState.length(); ++j) {
                if (inputBoardState[j] == 'x') {
                    copyBoardState = inputBoardState;
                    copyBoardState[i] = 'x';
                    copyBoardState[j] = 'W';
                    if (close_mill(j)) {
                        generate_remove();
                    } else {
                        boardStates.push_back(copyBoardState);
                    }
                }
            }
        }
    }
    // RESET THE COPY FOR USE IN OTHER FUNCTIONS AND RETURN THE FUNCTION RESULT
    //------------------------------------------------------------------------//
    copyBoardState = "";
    return boardStates;
} // generate_hopping()

void MoveGen::generate_remove() {
    bool nothingAddedToBoard = true;
    std::string localBoardCopy = copyBoardState;
    for (int i = 0; i < localBoardCopy.length(); ++i) {
        if (localBoardCopy[i] == 'B') {
            if (!close_mill(i)) {
                copyBoardState = localBoardCopy;
                copyBoardState[i] = 'x';
                boardStates.push_back(copyBoardState);
                nothingAddedToBoard = false;
            }
        }
    }
    if (nothingAddedToBoard) {
        for (int i = 0; i < localBoardCopy.length(); ++i) {
            if (localBoardCopy[i] == 'B') {
                copyBoardState = localBoardCopy;
                copyBoardState[i] = 'x';
                boardStates.push_back(copyBoardState);
            }
        }
    }
    // RESET THE COPY FOR USE IN OTHER FUNCTIONS AND RETURN THE FUNCTION RESULT
    //------------------------------------------------------------------------//
    copyBoardState = "";
} // generate_remove()

int* MoveGen::neighbors(const int& l) {

    // N WILL EITHER HAVE 3 OR 4 NEIGHBORS. n[0] IS N SIZE
    //------------------------------------------------------------------------//
    int numOfNeighbors = (
        l == 9 || l == 18 || l == 12 || l == 3 || l == 5 || l == 17 || l == 19
        ) ? 5 : 4;
    int* n = new int[numOfNeighbors];
    n[0] = numOfNeighbors;
    for (int i = 1; i < n[0]; ++i)
        *(n + i) = -1;
    //------------------------------------------------------------------------//

    //************************************************************************//
    // A COPY OF VARIANT D FOR EASY REFERENCE
    //************************************************************************//
    //
    //                      a   b   c   d   e   f   g
    //                    6 0-----------1-----------2 6 20's
    //                      | *         |         * |
    //                    5 |   7-------8-------9   | 5
    //                      |   | *     |     * |   |
    //                    4 |   |   4---5---6   |   | 4
    //                      |   |   |       |   |   |
    //                    3 8---9---0       1---2---3 3 10's
    //                      |   |   |       |   |   |
    //                    2 |   |   6-------7   |   | 2
    //                      |   | *           * |   |
    //                    1 |   3-------4-------5   | 1
    //                      | *         |         * |
    //                    0 0-----------1-----------2 0 0's
    //                      a   b   c   d   e   f   g
    //
    //************************************************************************//

    // FILL N WITH L'S NEIGHBORS
    //------------------------------------------------------------------------//
    switch (l) {
        case 0: {  // (a0)
            *(n + 1) = 8;
            *(n + 2) = 3;
            *(n + 3) = 1;
            break;
        }
        case 1: {  // (d0)
            *(n + 1) = 0;
            *(n + 2) = 4;
            *(n + 3) = 2;
            break;
        }
        case 2: {  // (g0)
            *(n + 1) =  1;
            *(n + 2) =  5;
            *(n + 3) = 13;
            break;
        }
        case 3: {  // (b1)
            *(n + 1) =  0;
            *(n + 2) =  9;
            *(n + 3) =  6;
            *(n + 4) =  4;
            break;
        }
        case 4: {  // (d1)
            *(n + 1) = 3;
            *(n + 2) = 5;
            *(n + 3) = 1;
            break;
        }
        case 5: {  // (f1)
            *(n + 1) =  4;
            *(n + 2) =  7;
            *(n + 3) = 12;
            *(n + 4) =  2;
            break;
        }
        case 6: {  // (c2)
            *(n + 1) =  3;
            *(n + 2) = 10;
            *(n + 3) =  7;
            break;
        }
        case 7: {  // (e2)
            *(n + 1) =  6;
            *(n + 2) = 11;
            *(n + 3) =  5;
            break;
        }
        case 8: {  // (a3)
            *(n + 1) = 20;
            *(n + 2) =  9;
            *(n + 3) =  0;
            break;
        }
        case 9: {  // (b3)
            *(n + 1) =  8;
            *(n + 2) = 17;
            *(n + 3) = 10;
            *(n + 4) =  3;
            break;
        }
        case 10: {  // (c3)
            *(n + 1) =  9;
            *(n + 2) = 14;
            *(n + 3) =  6;
            break;
        }
        case 11: {  // (e3)
            *(n + 1) = 16;
            *(n + 2) = 12;
            *(n + 3) =  7;
            break;
        }
        case 12: {  // (f3)
            *(n + 1) = 11;
            *(n + 2) = 19;
            *(n + 3) = 13;
            *(n + 4) =  5;
            break;
        }
        case 13: {  // (g3)
            *(n + 1) = 12;
            *(n + 2) = 22;
            *(n + 3) =  2;
            break;
        }
        case 14: {  // (c4)
            *(n + 1) = 17;
            *(n + 2) = 15;
            *(n + 3) = 10;
            break;
        }
        case 15: {  // (d4)
            *(n + 1) = 14;
            *(n + 2) = 18;
            *(n + 3) = 16;
            break;
        }
        case 16: {  // (e4)
            *(n + 1) = 15;
            *(n + 2) = 19;
            *(n + 3) = 11;
            break;
        }
        case 17: {  // (b5)
            *(n + 1) = 20;
            *(n + 2) = 18;
            *(n + 3) = 14;
            *(n + 4) =  9;
            break;
        }
        case 18: {  // (d5)
            *(n + 1) = 17;
            *(n + 2) = 21;
            *(n + 3) = 19;
            *(n + 4) = 15;
            break;
        }
        case 19: {  // (f5)
            *(n + 1) = 18;
            *(n + 2) = 22;
            *(n + 3) = 12;
            *(n + 4) = 16;
            break;
        }
        case 20: {  // (a6)
            *(n + 1) =  8;
            *(n + 2) = 17;
            *(n + 3) = 21;
            break;
        }
        case 21: {  // (d6)
            *(n + 1) = 20;
            *(n + 2) = 22;
            *(n + 3) = 18;
            break;
        }
        case 22: {  // (g6)
            *(n + 1) = 21;
            *(n + 2) = 19;
            *(n + 3) = 13;
            break;
        }
        default: break;
    }
    //------------------------------------------------------------------------//
    return n;
} // neighbors()

bool MoveGen::close_mill(const int& l) {

    // C CANNOT BE EMPTY SQUARE 'x'
    //------------------------------------------------------------------------//
    char c = copyBoardState[l];

    // CHECK CURRENT SQUARE l FOR A MILL (3 SQUARES OF SAME c IN A ROW/COL/DIAG)
    //------------------------------------------------------------------------//
    switch (l) {
        case 0: {
            if ((copyBoardState[1] == c && copyBoardState[2] == c) ||
                (copyBoardState[3] == c && copyBoardState[6] == c) ||
                (copyBoardState[8] == c && copyBoardState[20] == c)
                ) {
                    return true;
            } else {
                return false;
            }
        }
        case 1: {
            if (copyBoardState[0] == c && copyBoardState[2] == c) {
                return true;
            } else {
                return false;
            }
        }
        case 2: {
            if ((copyBoardState[0] == c && copyBoardState[1] == c) ||
                (copyBoardState[13] == c && copyBoardState[22] == c) ||
                (copyBoardState[7] == c && copyBoardState[5] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 3: {
            if ((copyBoardState[0] == c && copyBoardState[6] == c) ||
                (copyBoardState[4] == c && copyBoardState[5] == c) ||
                (copyBoardState[17] == c && copyBoardState[9] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 4: {
            if (copyBoardState[3] == c && copyBoardState[5] == c) {
                return true;
            } else {
                return false;
            }
        }
        case 5: {
            if ((copyBoardState[7] == c && copyBoardState[2] == c) ||
                (copyBoardState[3] == c && copyBoardState[4] == c) ||
                (copyBoardState[12] == c && copyBoardState[19] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 6: {
            if ((copyBoardState[10] == c && copyBoardState[14] == c) ||
                (copyBoardState[3] == c && copyBoardState[0] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 7: {
            if ((copyBoardState[11] == c && copyBoardState[16] == c) ||
                (copyBoardState[5] == c && copyBoardState[2] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 8: {
            if ((copyBoardState[0] == c && copyBoardState[20] == c) ||
                (copyBoardState[9] == c && copyBoardState[10] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 9: {
            if ((copyBoardState[8] == c && copyBoardState[10] == c) ||
                (copyBoardState[3] == c && copyBoardState[17] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 10: {
            if ((copyBoardState[8] == c && copyBoardState[9] == c) ||
                (copyBoardState[14] == c && copyBoardState[6] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 11: {
            if ((copyBoardState[16] == c && copyBoardState[7] == c) ||
                (copyBoardState[12] == c && copyBoardState[13] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 12: {
            if ((copyBoardState[11] == c && copyBoardState[13] == c) ||
                (copyBoardState[19] == c && copyBoardState[5] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 13: {
            if ((copyBoardState[11] == c && copyBoardState[12] == c) ||
                (copyBoardState[22] == c && copyBoardState[2] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 14: {
            if ((copyBoardState[10] == c && copyBoardState[6] == c) ||
                (copyBoardState[17] == c && copyBoardState[20] == c) ||
                (copyBoardState[15] == c && copyBoardState[16] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 15: {
            if ((copyBoardState[14] == c && copyBoardState[16] == c) ||
                (copyBoardState[18] == c && copyBoardState[21] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 16: {
            if ((copyBoardState[14] == c && copyBoardState[15] == c) ||
                (copyBoardState[11] == c && copyBoardState[7] == c) ||
                (copyBoardState[19] == c && copyBoardState[22] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 17: {
            if ((copyBoardState[18] == c && copyBoardState[19] == c) ||
                (copyBoardState[9] == c && copyBoardState[3] == c) ||
                (copyBoardState[20] == c && copyBoardState[14] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 18: {
            if ((copyBoardState[21] == c && copyBoardState[15] == c) ||
                (copyBoardState[17] == c && copyBoardState[19] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 19: {
            if ((copyBoardState[22] == c && copyBoardState[16] == c) ||
                (copyBoardState[17] == c && copyBoardState[18] == c) ||
                (copyBoardState[12] == c && copyBoardState[5] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 20: {
            if ((copyBoardState[8] == c && copyBoardState[0] == c) ||
                (copyBoardState[21] == c && copyBoardState[22] == c) ||
                (copyBoardState[17] == c && copyBoardState[14] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 21: {
            if ((copyBoardState[20] == c && copyBoardState[22] == c) ||
                (copyBoardState[18] == c && copyBoardState[15] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        case 22: {
            if ((copyBoardState[21] == c && copyBoardState[20] == c) ||
                (copyBoardState[13] == c && copyBoardState[2] == c) ||
                (copyBoardState[19] == c && copyBoardState[16] == c)
                ) {
                return true;
            } else {
                return false;
            }
        }
        default: return false;
    }
} // close_mill()
//============================================================================//

// GETTERS AND SETTERS
//============================================================================//
std::vector<std::string> MoveGen::get_board_states() {
    return boardStates;
}

std::string MoveGen::get_input_board_state() {
    return inputBoardState;
}

std::string MoveGen::get_copy_board_state() {
    return copyBoardState;
}

void MoveGen::set_board_states(std::vector<std::string> boardStates) {
    this->boardStates = boardStates;
}

void MoveGen::set_input_board_state(std::string inputBoardState) {
    this->inputBoardState = inputBoardState;
}

void MoveGen::set_copy_board_state(std::string copyBoardState) {
    this->copyBoardState = copyBoardState;
}
//============================================================================//