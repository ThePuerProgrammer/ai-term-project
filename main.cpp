//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * MINIMAXOPENING PROGRAM
// * MAIN 
//============================================================================//

// INCLUDES
//============================================================================//
#include <iostream>
#include <fstream>
#include "GUI.h"
//============================================================================//

// MAIN *ACCEPTS COMMAND LINE ARGS*
//============================================================================//
int main(int argc, char *argv[]) {

    // INITIALIZE LOCAL VARIABLES
    //------------------------------------------------------------------------//
    int searchDepth = 0, positionsEvaluated = 0, miniMaxEstimate = 0;
    std::string inputBoardPos = "", outputBoardPos = "";
    //------------------------------------------------------------------------//

    //************************************************************************//
    // START OF COMMAND LINE EXCEPTION HANDLING SECTION
    //************************************************************************//

    // PARTIAL TEST FOR VALID C.L.A. FORMATTING
    //------------------------------------------------------------------------//
    if (argc != 4) {
        std::cout << "Command line arguments not properly formatted. "
                  << "Program terminated.\n" 
                  << "EXAMPLE: ./MiniMaxOpening in.txt out.txt 2" << std::endl;
        return 0xCA; // 202
    }
    //------------------------------------------------------------------------//

    // OPEN REQUIRED INPUT FILE FROM C.L.A. IN POS 1 AND TEST FOR ERRORS
    //------------------------------------------------------------------------//
    std::fstream inputFile;
    inputFile.open(argv[1], std::ios::in);
    if (!inputFile) {
        std::cout << "Input file could not be opened. Program terminated." 
                  << std::endl;
        return 0xFE; // 254
    }
    //------------------------------------------------------------------------//

    // OPEN REQUIRED OUTPUT FILE FROM C.L.A. IN POS 2 AND TEST FOR ERRORS
    //------------------------------------------------------------------------//
    std::fstream outputFile;
    outputFile.open(argv[2], std::ios::out);
    if (!outputFile) {
        std::cout << "Output file could not be opened. Program terminated." 
                  << std::endl;
        return 0xFE; // 254
    }
    //------------------------------------------------------------------------//

    // TEST THAT THE FOURTH ARGUMENT IS AN INTEGER
    //------------------------------------------------------------------------//
    try {
        searchDepth = std::stoi(argv[3]);
    } catch (...) {
        std::cout << "argv[3]: " << argv[3] << " is invalid type." << std::endl;
        std::cout << "Fourth command line argument must be of type int. "
                  << "Program Terminated." << std::endl;
        return 0xCA; // 202
    }
    //------------------------------------------------------------------------//

    //************************************************************************//
    // END OF COMMAND LINE EXCEPTION HANDLING SECTION
    //************************************************************************//
    
    //************************************************************************//
    // START OF GAME LOGIC SECTION
    //************************************************************************//

    // GET THE CURRENT BOARD POSITION FROM THE INPUT FILE AND TEST FOR ERRORS
    //------------------------------------------------------------------------//
    try {
        getline(inputFile, inputBoardPos);
        if (inputBoardPos.length() != 23) 
            throw std::runtime_error("Invalid board position length");
    } catch (std::runtime_error& e) {
        std::cout << e.what() << "\n"
                  << "REQUIRED EXAMPLE: xxxxWxBBxxxxWxxxxxBBxxxx."
                  << std::endl;
    } catch (...) {
        std::cout << "The provided input file isn't properly formatted.\n"
                  << "REQUIRED EXAMPLE: xxxxWxBBxxxxWxxxxxBBxxxx"
                  << std::endl;
        return 0xFE; // 254
    }
    //------------------------------------------------------------------------//

    // GUI CLASS PRINTS A REPRESENTATION OF THE BOARD IN THE TERMINAL
    //------------------------------------------------------------------------//
    GUI gui(inputBoardPos);
    gui.print_board();
    //------------------------------------------------------------------------//

    // PRINT INPUT_POS/OUTPUT_POS/TOTAL_EVALUATIONS/MINIMAX_ESTIMATE
    //------------------------------------------------------------------------//
    std::cout << "Input position: " << inputBoardPos << std::endl;
    std::cout << "Output position: " << outputBoardPos << std::endl;
    std::cout << "Positions evaluated by static esitmation: " 
              << positionsEvaluated << std::endl;
    std::cout << "MINIMAX estimate: " << miniMaxEstimate << std::endl;
    //------------------------------------------------------------------------//

    //************************************************************************//
    // END OF GAME LOGIC SECTION
    //************************************************************************//

    // CLOSE I/O FILES BEFORE PROGRAM TERMINATION
    //------------------------------------------------------------------------//
    inputFile.close();
    outputFile.close();
    //------------------------------------------------------------------------//

    // TERMINATE PROGRAM SUCCESSFULLY 
    //------------------------------------------------------------------------//
    return 0;
}
//============================================================================//