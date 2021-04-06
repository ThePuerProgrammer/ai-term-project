//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * MINIMAX OPENING PROGRAM
// * AI THAT PLAYS NINE MENS MORRIS BETTER THAN YOU
// * MAIN 
//============================================================================//

// PREPROCESSORS
//============================================================================//
#define TIME_LIMIT 119
//============================================================================//

// INCLUDES
//============================================================================//
#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "GUI.h"
#include "MoveGen.h"
#include "StaticEstimation.h"
#include "StateNode.h"
#include "StateTool.h"
//============================================================================//

// FORWARD DECLARATIONS / PROTOTYPES
//============================================================================//
std::pair<int, int> mini_max(StateNode*, int, int, bool);
std::string witty_response(int);
//============================================================================//

// GLOBAL VARIABLES
//============================================================================//
std::chrono::steady_clock::time_point t, b, e;
bool timerRanOut = false;
//============================================================================//

// NAMESPACES
//============================================================================//
using namespace std::chrono;
//============================================================================//

// MAIN *ACCEPTS COMMAND LINE ARGS*
//============================================================================//
int main(int argc, char *argv[]) {

    // INITIALIZE LOCAL VARIABLES
    //------------------------------------------------------------------------//
    int searchDepth = 0, positionsEvaluated = 0, miniMaxEstimate = 0;
    int indexOfBestMove = -1;
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
                  << "EXAMPLE: ./miniMaxOpening in.txt out.txt 2" << std::endl;
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
        std::cout << "Fourth command line argument must be of type int.\n"
                  << "EXAMPLE: ./miniMaxOpening in.txt out.txt 2\n"
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
        // THERE SHOULD ONLY BE ONE LINE IN THE INPUT FILE
        //--------------------------------------------------------------------//
        getline(inputFile, inputBoardPos);

        // BOARD LENGTH MUST BE 23
        //--------------------------------------------------------------------//
        if (inputBoardPos.length() != 23) 
            throw std::runtime_error("Invalid board position length");

        // IF THERE ARE 9 WHITE PIECES THE OPENING IS OVER. DON'T CONTINUE
        //--------------------------------------------------------------------//
        int wC = std::count(inputBoardPos.begin(), inputBoardPos.end(), 'W');
        if (wC >= 9)
            throw std::runtime_error("Too many white pieces on the board");
    } catch (std::runtime_error& e) {
        std::cout << e.what() << "\n"
                  << "REQUIRED EXAMPLE: xxxxWxBBxxxxWxxxxxBBxxxx."
                  << std::endl;
        return 0xFE; // 254
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

    // NODE STRUCTURE IS USED TO CREATE A TREE OF FUTURE STATES FROM ROOT STATE
    // STATENODE(BOARD STATES VECTOR, HEIGHT, CURRENT DEPTH)
    //------------------------------------------------------------------------//
    std::vector<std::string> onlyInputState;
    onlyInputState.push_back(inputBoardPos);
    StateNode rootNode(onlyInputState, searchDepth, 0); 
    //------------------------------------------------------------------------//

    // t REPRESENTS TOTAL ALGORITHM RUN TIME AND CAN SERVE AS OUR TIME LIMIT
    //------------------------------------------------------------------------//
    t = steady_clock::now();
    //------------------------------------------------------------------------//

    // FOR OUR PURPOSES P IS THE ROOT NODE. POPULATE ITS CHILDREN
    //------------------------------------------------------------------------//
    StateNode* p = &rootNode;
    MoveGen moveGen(p->get_board_states()[0]);
    std::vector<std::string> m = moveGen.generate_moves_opening();
    p->add_child(m);
    //------------------------------------------------------------------------//

    // RUN MINIMAX WITH !!PROGRESSIVE DEEPENING!!
    // USING PROGRESSIVE DEEPENING FROM A DEPTH OF 1 PROVIDES MOVE INSURANCE
    //------------------------------------------------------------------------//
    std::cout << "\n( ु⁎ᴗ_ᴗ⁎)ु.｡oO ┬─┬ （＾－＾゛）\n" << std::endl; 
    if (inputBoardPos != "xxxxxxxxxxxxxxxxxxxxxxx")
        std::cout << "hmm... that's an interesting move\n" << std::endl;
    std::cout << "***RUNNING MINIMAX ALGORITHM***\n" << std::endl;

    for (int i = 1; i <= searchDepth; i++) {
        std::cout << "Evaluating " << i << " move(s) into the future." 
                  << std::endl;

        // START CLOCK
        //--------------------------------------------------------------------//
        b = steady_clock::now();

        // VECTOR STORES THE BEST INDEX RESULTS OF EVERY RUN OF MINMAX
        //--------------------------------------------------------------------//
        std::vector<int> allIndexes;

        // THIS IS THE BRAIN OF THE OPERATION
        //--------------------------------------------------------------------//
        for (int j = 0; j < p->get_child_nodes().size(); ++j) {

            // MINIMAX HAPPENS HERE
            std::pair<int, int> bestMove = mini_max(
                p->get_child_nodes()[j], j, i, whitesTurn
            );

            // STORE THEM ALL IN CASE WE NEED TO STOP
            //----------------------------------------------------------------//
            allIndexes.push_back(bestMove.second);

            // IF INDEX -1 THEN TIMER RAN OUT OR TOO MANY PIECES 
            //----------------------------------------------------------------//
            if (bestMove.second != -1) {

                // IF THE TIMER RAN OUT MID SEARCH AT DEPTH N, BEST ESTIMATE
                // FOR DEPTH N MUST BE BETTER THAN BEST ESTIMATE AT N - 1 IN
                // ORDER TO SET THE RESULT TO INDEX AT N
                //------------------------------------------------------------//
                if ((timerRanOut && bestMove.first >= miniMaxEstimate) ||
                    !timerRanOut
                    ) {
                    // SET RESULTS
                    //--------------------------------------------------------//
                    miniMaxEstimate = bestMove.first;
                    indexOfBestMove = bestMove.second;
                }
            }
        }

        std::cout << "Evaluating to depth " << i << " took "
                  << duration_cast<seconds>(e - b).count() << "[s] to complete"
                  << std::endl;

        std::cout << "\n'" << witty_response(i) << "'\n" << std::endl;

        // TIME LIMIT EVALUATION
        //--------------------------------------------------------------------//
        e = steady_clock::now();
        if (duration_cast<seconds>(e - t).count() > TIME_LIMIT) break;

        // A RESULT THAT WASN'T -1 MEANS THERE'S STILL FURTHER STATES TO EXPLORE
        //--------------------------------------------------------------------//
        bool boardIsFull = true;
        for (int j = 0; j < allIndexes.size(); ++j)
            if (allIndexes[j] != -1) boardIsFull = false;

        // THEY WERE ALL -1. IT'S OVER
        //--------------------------------------------------------------------//
        if (boardIsFull) break;
    }
    //------------------------------------------------------------------------//

    // GET THE STATIC 'POSITIONS EVALUATED' VARIABLE OUT OF STATIC ESTIMATION
    //------------------------------------------------------------------------//
    StaticEstimation staticEstimation(1);
    positionsEvaluated = staticEstimation.positionsEvaluated;
    //------------------------------------------------------------------------//

    // RESULTING BOARD POSITION
    //------------------------------------------------------------------------//
    outputBoardPos = 
        p->get_child_nodes()[0]->get_board_states()[indexOfBestMove];
    //------------------------------------------------------------------------//

    // STOP TOTAL TIME ELAPSED CLOCK AND PRINT RESULTS
    //------------------------------------------------------------------------//
    e = std::chrono::steady_clock::now();
    std::cout << "Total time expended for AI move selection: " 
              << std::chrono::duration_cast<std::chrono::seconds>(e - t).count() 
              << "[s]" << std::endl;
    //------------------------------------------------------------------------//

    // WRITE OUTPUT BOARD POSITION TO OUTPUT FILE 
    //------------------------------------------------------------------------//
    outputFile << outputBoardPos << std::endl;
    //------------------------------------------------------------------------//

    // FINAL RESULTS
    // PRINT BOARD/INPUT_POS/OUTPUT_POS/TOTAL_EVALUATIONS/MINIMAX_ESTIMATE
    //------------------------------------------------------------------------//
    std::cout << "Output board position: " << std::endl;
    gui.set_board_pos(outputBoardPos);
    gui.print_board();
    
    std::cout << "\n\nGET REKT (ノ °益°)ノ 彡 (\\.o.)\\\n\n" << std::endl;
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

    // TERMINATE PROGRAM SUCCESSFULLY (ง⇀Ѡ↼)ง
    //------------------------------------------------------------------------//
    return 0;
}
//============================================================================//

// MINIMAX RECURSIVE FUNCTION. BOOL EITHER MAX OR MIN (!MAX)
//============================================================================//
std::pair<int, int> mini_max(
    StateNode* p, int index, int maxDepth, bool max
    ) {

    // THIS GUARDS AGAINST RUNNING OVER THE TIME LIMIT OF 2 MINUTES
    //------------------------------------------------------------------------//
    e = steady_clock::now();
    if (duration_cast<seconds>(e - t).count() > TIME_LIMIT) {

        // SETTING TIMER RAN OUT TO TRUE MAKES THE ALGORITHM CHOOSE THE PREVIOUS
        // DEPTH ESTIMATE WHEN THIS FUNCTION RETURNS ITS FINAL RESULT
        //--------------------------------------------------------------------//
        timerRanOut = true;
        return std::make_pair(-2147483648, -1);
    }
    //------------------------------------------------------------------------//

    // ONLY PROCEED TO MAX DEPTH
    //------------------------------------------------------------------------//
    if (p->get_depth() < maxDepth) {

        // NUMBER OF CHILD NODES
        //--------------------------------------------------------------------//
        int numOfChildren = p->get_child_nodes().size();
    
        // TRACKS THE MINIMAX ESTIMATE AND INDEX
        // IF MAX THEN MAX ELSE IF !MAX THEN MIN
        //--------------------------------------------------------------------//
        std::vector<std::pair<int, int> > miniMaxScoreAndIndex;

        // THIS ALLOWS FOR PROGRESSIVE DEEPENING. ELSE DONT GENERATE NEW NODES
        //--------------------------------------------------------------------//
        if (numOfChildren == 0) {

            // LOOP THROUGH EVERY BOARD STATE IN THE NODES STATE ARRAY
            //----------------------------------------------------------------//
            for (int i = 0; i < p->get_board_states().size(); ++i) {

                // LOCAL VARIABLES
                //------------------------------------------------------------//
                std::string board = p->get_board_states()[i];
                StateTool tool;

                // ENSURE THAT THERE ARE VALID MOVES ON THE BOARD
                //------------------------------------------------------------//
                if (std::count(board.begin(), board.end(), 'W') > 9)
                    return std::make_pair(-2147483648, -1);
                
                if (std::count(board.begin(), board.end(), 'B') > 9)
                    return std::make_pair(-2147483648, -1);

                // IF MINS TURN, INVERT THE BOARD
                //------------------------------------------------------------//
                if (max) board = tool.get_invert_board(
                    p->get_board_states()[i]
                    );

                // GENERATE ALL POSSIBLE MOVES FROM THIS STATE
                //------------------------------------------------------------//
                MoveGen moveGen(board);
                std::vector<std::string> m = moveGen.generate_moves_opening();

                // IF MIN REVERT THE BOARD STATES FOR EVALUATION
                //------------------------------------------------------------//
                if (max)
                    for (int j = 0; j < m.size(); ++j)
                        m[j] = tool.get_invert_board(m[j]);
                
                // CONNECT THE NEW STATE NODE AND FILL ITS FUTURE STATES
                //------------------------------------------------------------//
                p->add_child(m);

                // CONTINUE THE RECURSIVE CALL (DEPTH FIRST)
                //------------------------------------------------------------//
                miniMaxScoreAndIndex.push_back(mini_max(
                    p->get_child_nodes()[i], i, maxDepth, !max)
                );
            }
        // ELSE CHILD NODES ARE ALREADY POPULATED
        //--------------------------------------------------------------------//
        } else {
            for (int i = 0; i < p->get_child_nodes().size(); ++i) {
                miniMaxScoreAndIndex.push_back(mini_max(
                    p->get_child_nodes()[i], i, maxDepth, !max)
                );
            }
        }
        //--------------------------------------------------------------------//

        // EVALUATE THE MIN OR MAX AND RETURN THE BEST RESULT
        //--------------------------------------------------------------------//
        if (max) {
            int maxEstimate = -2147483648;
            int maxIndex = -1;
            for (int i = 0; i < miniMaxScoreAndIndex.size(); ++i) {
                if (miniMaxScoreAndIndex[i].first > maxEstimate) {
                    maxEstimate = miniMaxScoreAndIndex[i].first;
                    maxIndex = i;
                }
            }
            return std::make_pair(maxEstimate, maxIndex);
        } else {
            int minEstimate = 2147483647;
            int minIndex = -1;
            for (int i = 0; i < miniMaxScoreAndIndex.size(); ++i) {
                if (miniMaxScoreAndIndex[i].first < minEstimate) {
                    minEstimate = miniMaxScoreAndIndex[i].first;
                    minIndex = i;
                }
            }
            return std::make_pair(minEstimate, minIndex);
        }
        //--------------------------------------------------------------------//

    // ELSE WE ARE EVALUATING THE LEAF NODES TO GET THE STATIC ESTIMATES
    //------------------------------------------------------------------------//
    } else {

        // STATIC ESTIMATION CLASS TO EVALUATE THE LEAF POSITIONS
        //--------------------------------------------------------------------//
        // std::cout << (max ? "max" : "min") << std::endl;
        // for (auto const &s : p->get_board_states()) {
        //     std::cout << s << std::endl;
        // }
        StaticEstimation staticEstimation(p->get_board_states(), max);
        staticEstimation.estimate_opening();
        int maxEstimation = staticEstimation.get_max_estimation();
        int minEstimation = staticEstimation.get_min_estimation();
        if (max) {
            return std::make_pair(maxEstimation, index);
        } else {
            return std::make_pair(minEstimation, index);
        } 
    }
}
//============================================================================//

// JUST A BIT OF FUN
//============================================================================//
std::string witty_response(int i) {
    switch (i) {
        case 1: return "I've got nothing";
        case 2: return "I can do better";
        case 3: return "This looks promising";
        case 4: return "Great move";
        case 5: return "You're getting smoked";
        case 6: return "I can see the future";
        case 7: return "2EZPZ";
        case 8: return "I could do this all day";
        default: return "You might as well resign";
    }
}
//============================================================================//