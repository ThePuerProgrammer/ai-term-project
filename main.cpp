//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * MINIMAXOPENING PROGRAM
// * AI THAT PLAYS NINE MENS MORRIS BETTER THAN YOU
// * MAIN 
//============================================================================//

// INCLUDES
//============================================================================//
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "GUI.h"
#include "MoveGen.h"
#include "StaticEstimation.h"
#include "StateNode.h"
#include "StateTool.h"
//============================================================================//

// FORWARD DECLARATIONS / PROTOTYPES
//============================================================================//
void recursiveTreeFill(StateNode*, int, bool);
//============================================================================//

// GLOBAL VARIABLES
//============================================================================//
std::unordered_map<std::string, std::pair<StateNode*, int> > cameFrom;
std::unordered_map<int, std::string> leafEstimation;
//============================================================================//

// MAIN *ACCEPTS COMMAND LINE ARGS*
//============================================================================//
int main(int argc, char *argv[]) {

    // INITIALIZE LOCAL VARIABLES
    //------------------------------------------------------------------------//
    int searchDepth = 0, positionsEvaluated = 0, miniMaxEstimate = 0;
    std::string inputBoardPos = "", outputBoardPos = "";
    bool whitesTurn = true;
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
    std::cout << "Input board position: " << std::endl;
    gui.print_board();
    //------------------------------------------------------------------------//

    // NODE STRUCTURE IS USED TO CREATE A TREE OF STATES FROM ROOT C.M.A. STATE
    //------------------------------------------------------------------------//
    std::vector<std::string> onlyInputState;
    onlyInputState.push_back(inputBoardPos);
    StateNode rootNode(onlyInputState, searchDepth, 0);
    //------------------------------------------------------------------------//

    // MOVE GENERATOR MAKES A LIST OF POSSIBLE MOVES FROM ANY BOARD STATE
    //------------------------------------------------------------------------//
    MoveGen moveGen(inputBoardPos);
    std::vector<std::string> openingMoves = moveGen.generateMovesOpening();
    //------------------------------------------------------------------------//

    // GIVE THE ROOT NODE ITS FIRST SET OF CHILD NODES AND GROW TO SEARCH DEPTH
    //------------------------------------------------------------------------//
    if (searchDepth >= 1) 
        rootNode.addChild(openingMoves);
    StateNode* p = rootNode.getChildNodes()[0];
    whitesTurn = !whitesTurn;
    recursiveTreeFill(p, searchDepth, whitesTurn);
    //------------------------------------------------------------------------//

    std::unordered_map<int, std::string>::iterator it = leafEstimation.begin();
    int max = -2147483648;
    for (;it != leafEstimation.end(); ++it) 
        if ((*it).first > max) max = (*it).first;


    std::string bestFinalState = leafEstimation.at(max);
    for (int i = 1; i < searchDepth; ++i) {
        StateNode* tracker = cameFrom.at(bestFinalState).first;
        int index = cameFrom.at(bestFinalState).second;
        bestFinalState = tracker->getBoardStates()[index];
    }

    StaticEstimation staticEstimation;
    positionsEvaluated = staticEstimation.positionsEvaluated;
    outputBoardPos = bestFinalState;
    miniMaxEstimate = max;

    // WRITE OUTPUT BOARD POSITION TO OUTPUT FILE 
    //------------------------------------------------------------------------//
    outputFile << outputBoardPos << std::endl;
    //------------------------------------------------------------------------//

    // PRINT BOARD/INPUT_POS/OUTPUT_POS/TOTAL_EVALUATIONS/MINIMAX_ESTIMATE
    //------------------------------------------------------------------------//
    gui.set_board_pos(outputBoardPos);
    std::cout << "Output board position: " << std::endl;
    gui.print_board();
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

// LOCAL FUNCTIONS
//============================================================================//
void recursiveTreeFill(StateNode* p, int maxDepth, bool whitesTurn) {

    // ONLY PROCEED TO MAX DEPTH
    //------------------------------------------------------------------------//
    if (p->getDepth() < maxDepth) {

        // LOOP THROUGH EVERY BOARD STATE IN THE NODES STATE ARRAY
        //--------------------------------------------------------------------//
        for (int i = 0; i < p->getBoardStates().size(); ++i) {

            // LOCAL VARIABLES
            //----------------------------------------------------------------//
            std::string board;
            StateTool tool;

            // IF BLACKS TURN, INVERT THE BOARD
            //----------------------------------------------------------------//
            if (!whitesTurn) {
                tool.setBoardState(p->getBoardStates()[i]);
                board = tool.getInvertBoard();
            } else {
                board = p->getBoardStates()[i];
            }

            // GENERATE ALL POSSIBLE MOVES FROM THIS STATE
            //----------------------------------------------------------------//
            MoveGen moveGen(board);
            std::vector<std::string> m = moveGen.generateMovesOpening();

            if (!whitesTurn) {
                for (int j = 0; j < m.size(); ++j) {
                    tool.setBoardState(m[j]);
                    m[j] = tool.getInvertBoard();
                }
            }
            
            // CONNECT THE NEW STATE NODE AND FILL ITS FUTURE STATES
            //----------------------------------------------------------------//
            p->addChild(m);

            // CREATE A TRACE FOR EVERY STATE
            //----------------------------------------------------------------//
            int size = p->getChildNodes()[i]->getBoardStates().size();
            for (int j = 0; j < size; ++j) {
                cameFrom.insert(
                    std::make_pair(
                        p->getChildNodes()[i]->getBoardStates()[j],
                        std::make_pair(p, j)
                    )
                );
                // std::cout << p->getChildNodes()[i]->getBoardStates()[j]
                //           << std::endl;
            }

            // CONTINUE THE RECURSIVE CALL
            //----------------------------------------------------------------//
            recursiveTreeFill(p->getChildNodes()[i], maxDepth, !whitesTurn);
        }
    } else {

        // STATIC ESTIMATION CLASS TO EVALUATE THE LEAF POSITIONS
        //--------------------------------------------------------------------//
        StaticEstimation staticEstimation(p->getBoardStates());
        staticEstimation.estimateOpening();
        int best = staticEstimation.getBestEstimation();
        int l = staticEstimation.getEstimationsMap().at(best);
        std::string pos = staticEstimation.getPositions()[l];
        leafEstimation.insert(std::make_pair(best, pos));
    }
}
//============================================================================//