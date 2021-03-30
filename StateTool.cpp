//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * STATE TOOL CLASS IMPLEMENTATION FILE 
// * GENERIC TOOLS FOR MANIPULATING AND EVALUATING A BOARD STATE
//============================================================================//

// INCLUDES
//============================================================================//
#include "StateTool.h"
//============================================================================//

// CONSTRUCTORS
//============================================================================//
StateTool::StateTool() {
    boardState = "";
}

StateTool::StateTool(std::string boardState) {
    this->boardState = boardState;
} 
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
std::string StateTool::getInvertBoard() {
    for (int i = 0; i < boardState.length(); ++i) {
        if (boardState[i] == 'W') {
            boardState[i] = 'B';
        } else if (boardState[i] == 'B') {
            boardState[i] = 'W';
        }
    }
    return boardState;
}
//============================================================================//

// GETTERS/SETTERS
//============================================================================//
void StateTool::setBoardState(std::string boardState) {
    this->boardState = boardState;
}
//============================================================================//