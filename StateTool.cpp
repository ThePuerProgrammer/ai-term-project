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
std::string StateTool::get_invert_board() {
    for (int i = 0; i < boardState.length(); ++i) {
        if (boardState[i] == 'W') {
            boardState[i] = 'B';
        } else if (boardState[i] == 'B') {
            boardState[i] = 'W';
        }
    }
    return boardState;
}

std::string StateTool::get_invert_board(std::string board) {
    for (int i = 0; i < board.length(); ++i) {
        if (board[i] == 'W') {
            board[i] = 'B';
        } else if (board[i] == 'B') {
            board[i] = 'W';
        }
    }
    return board;
}
//============================================================================//

// GETTERS/SETTERS
//============================================================================//
void StateTool::set_board_state(std::string boardState) {
    this->boardState = boardState;
}
//============================================================================//