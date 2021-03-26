//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * GUI CLASS IMPLEMENTATION FILE
// * ADDS TERMINAL UI FUNCTIONALITY
//============================================================================//

// INCLUDES
//============================================================================//
#include <iostream>
#include "GUI.h"
//============================================================================//

// STATIC VARS
//============================================================================//
int GUI::boardSize = 3;
//============================================================================//

// CONSTRUCTORS
//============================================================================//
GUI::GUI() {
    // LENGTH MUST BE 23 TO MATCH BOARD
    boardPos = "xxxxxxxxxxxxxxxxxxxxxxx";
}

GUI::GUI(std::string boardPos) {
    this->boardPos = boardPos;
}
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
void GUI::print_board() {

    // ASSERT STRING LENGTH IS VALID ELSE RETURN
    //------------------------------------------------------------------------//
    if (boardPos.length() != 23) {
        std::cout << "Invalid Configuration. Position str must be 23 chars." 
                  << std::endl;
        return;
    }
    //------------------------------------------------------------------------//

    // PRINT IT. ASTERISKS ARE DIAGONALS. ORGANIZED BY ROW AND THEN COLUMN.
    //------------------------------------------------------------------------//
    std::cout << std::endl;

              // R6
              //--------------------------------------------------------------//
    std::cout << boardPos[20] << std::string(boardSize * 3 + 2, '-')       // C0
              << boardPos[21] << std::string(boardSize * 3 + 2, '-')       // C3
              << boardPos[22] << "\n"                                      // C6

              // SPACER
              //--------------------------------------------------------------//
              << "|"  << std::string(boardSize / 2, ' ')
              << "*"  << std::string(boardSize * 2 + 2 + boardSize / 2, ' ')
              << "|"  << std::string(boardSize * 2 + 2 + boardSize / 2, ' ')
              << "*"  << std::string(boardSize / 2, ' ')
              << "|"  << "\n"
              
              // R5
              //--------------------------------------------------------------//
              << "|"  << std::string(boardSize, ' ')
              << boardPos[17] << std::string(boardSize * 2 + 1, '-')       // C1
              << boardPos[18] << std::string(boardSize * 2 + 1, '-')       // C3
              << boardPos[19] << std::string(boardSize, ' ')               // C5
              << "|"  << "\n"

              // SPACER
              //--------------------------------------------------------------//
              << "|"  << std::string(boardSize, ' ')
              << "|"  << std::string(boardSize / 2, ' ')
              << "*"  << std::string(boardSize / 2 + boardSize + 1, ' ')
              << "|"  << std::string(boardSize / 2 + boardSize + 1, ' ')
              << "*"  << std::string(boardSize / 2, ' ')
              << "|"  << std::string(boardSize, ' ') 
              << "|"  << "\n"

              // R4
              //--------------------------------------------------------------//
              << "|"  << std::string(boardSize, ' ')
              << "|"  << std::string(boardSize, ' ')
              << boardPos[14] << std::string(boardSize, '-')               // C2
              << boardPos[15] << std::string(boardSize, '-')               // C3
              << boardPos[16] << std::string(boardSize, ' ')               // C4
              << "|"  << std::string(boardSize, ' ')
              << "|"  << "\n"

              // SPACER
              //--------------------------------------------------------------//
              << "|"  << std::string(boardSize, ' ')
              << "|"  << std::string(boardSize, ' ')
              << "|"  << std::string(boardSize * 2 + 1, ' ')
              << "|"  << std::string(boardSize, ' ')
              << "|"  << std::string(boardSize, ' ') 
              << "|"  << "\n"

              // R3
              //--------------------------------------------------------------//
              << boardPos[11] << std::string(boardSize, '-')               // C0
              << boardPos[12] << std::string(boardSize, '-')               // C1
              << boardPos[13] << std::string(boardSize, ' ')               // C2
              << " "   << std::string(boardSize, ' ')
              << boardPos[8]  << std::string(boardSize, '-')               // C4
              << boardPos[9]  << std::string(boardSize, '-')               // C5
              << boardPos[10] << "\n"                                      // C6

              // SPACER
              //--------------------------------------------------------------//
              << "|"   << std::string(boardSize, ' ')
              << "|"   << std::string(boardSize, ' ')
              << "|"   << std::string(boardSize * 2 + 1, ' ')
              << "|"   << std::string(boardSize, ' ')
              << "|"   << std::string(boardSize, ' ') 
              << "|"   << "\n"

              // R2
              //--------------------------------------------------------------//
              << "|"   << std::string(boardSize, ' ')
              << "|"   << std::string(boardSize, ' ')
              << boardPos[6] << std::string(boardSize, '-')                // C2
              << std::string(boardSize + 1, '-')         
              << boardPos[7] << std::string(boardSize, ' ')                // C4
              << "|"   << std::string(boardSize, ' ')
              << "|"   << "\n"

              // SPACER
              //--------------------------------------------------------------//
              << "|"   << std::string(boardSize, ' ')
              << "|"   << std::string(boardSize / 2, ' ')
              << "*"   << std::string(boardSize / 2 + boardSize + 1, ' ')
              << std::string(boardSize / 2 + boardSize + 2, ' ')
              << "*"   << std::string(boardSize / 2, ' ')
              << "|"   << std::string(boardSize, ' ') 
              << "|"   << "\n"

              // R1
              //--------------------------------------------------------------//
              << "|"   << std::string(boardSize, ' ')
              << boardPos[3] << std::string(boardSize * 2 + 1, '-')        // C1
              << boardPos[4] << std::string(boardSize * 2 + 1, '-')        // C3
              << boardPos[5] << std::string(boardSize, ' ')                // C5
              << "|"   << "\n"

              // SPACER
              //--------------------------------------------------------------//
              << "|"   << std::string(boardSize / 2, ' ')
              << "*"   << std::string(boardSize * 2 + 2 + boardSize / 2, ' ')
              << "|"   << std::string(boardSize * 2 + 2 + boardSize / 2, ' ')
              << "*"   << std::string(boardSize / 2, ' ') 
              << "|"   << "\n"

              // R0
              //--------------------------------------------------------------//
              << boardPos[0] << std::string(boardSize * 3 + 2, '-')        // C0
              << boardPos[1] << std::string(boardSize * 3 + 2, '-')        // C3
              << boardPos[2] << "\n"                                       // C6

              << std::endl; // END PRINT
    //------------------------------------------------------------------------//
}
//============================================================================//

// GETTERS AND SETTERS
//============================================================================//
std::string GUI::get_board_pos() {
    return boardPos;
}

void GUI::set_board_pos(std::string boardPos) {
    this->boardPos = boardPos;
}
//============================================================================//