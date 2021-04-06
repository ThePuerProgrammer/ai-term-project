//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * STATIC ESTIMATION CLASS IMPLEMENTATION FILE 
// * EVALUATES A LIST OF GENERATED POSSIBILITIES FOR OPTIMAL OUTCOME
//============================================================================//

// INCLUDES
//============================================================================//
#include "StaticEstimation.h"
#include "MoveGen.h"
//============================================================================//

// STATIC IMPLEMENTATION
//============================================================================//
int StaticEstimation::positionsEvaluated = 0;
//============================================================================//

// CONSTRUCTORS
//============================================================================//
StaticEstimation::StaticEstimation() {
    this->whitesTurn = true;
}

StaticEstimation::StaticEstimation(bool whitesTurn) {
    this->whitesTurn = whitesTurn;
} // StaticEstimation()

StaticEstimation::StaticEstimation(
    std::vector<std::string> positions, bool whitesTurn
    ) {
    this->positions = positions;
    this->whitesTurn = whitesTurn;
} // StaticEstimation(std::vector<std::string>)
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
void StaticEstimation::estimate_opening() {

    // VARIABLE SET TO INT_MIN WILL TRACE BEST ESTIMATION
    //------------------------------------------------------------------------//
    int posSize = positions.size();
    int bestimation = -2147483648;
    int worstimation = 2147483647;

    // FOR EVERY BOARD POSITION IN POSITIONS
    //------------------------------------------------------------------------//
    for (int i = 0; i < posSize; ++i) {

        ++positionsEvaluated;
        
        // GET WHITE COUNT MINUS BLACK COUNT
        //--------------------------------------------------------------------//
        int whiteCount = number_of_pieces(positions[i], 'W');
        int blackCount = number_of_pieces(positions[i], 'B');
        int whiteMinusBlack = whiteCount - blackCount;

        // CHECK WHICH PLAYER HAS MORE LOCKED PIECES
        //--------------------------------------------------------------------//
        int numOfWhiteNeighbors = number_of_neighbors(positions[i], 'W');
        int numOfBlackNeighbors = number_of_neighbors(positions[i], 'B');

        // IF WHITE HAS FEWER LOCKED PIECES
        //--------------------------------------------------------------------//
        if (numOfWhiteNeighbors > numOfBlackNeighbors) {
            whiteMinusBlack++;
        }

        // UPDATE MAX AND MIN ESTIMATION IF NEEDED
        //--------------------------------------------------------------------//
        if (whiteMinusBlack > bestimation)
            bestimation = whiteMinusBlack;

        if (whiteMinusBlack < worstimation)
            worstimation = whiteMinusBlack;
    }
    //------------------------------------------------------------------------//

    // SET THE FINAL BEST ESTIMATION FOR GETTER
    //------------------------------------------------------------------------//
    maxEstimation = bestimation;
    minEstimation = worstimation;
}

//############################################################################//
// POSSIBLE IDEA TO EXAMINE THE MANHATTAN DISTANCES FROM EACH PIECE TO A MILL
// RETIRED FOR THE MOMENT
//############################################################################//
// int StaticEstimation::distance_from_mills(std::string position) {
//     int distance = 0;
//     MoveGen moveGen(position);
//     for (int i = 0; i < position.length(); ++i) {
//         if (position[i] == 'W') {
//             for (int j = 0; j < position.length(); ++j) {
//                 if (j == i) continue;
//                 int* p = moveGen.neighbors(j);
//                 int counter = 0;
//                 for (int k = 1; k < p[0]; ++k)
//                     if (p[k] == 'W') ++counter;

//                 if (counter >= 2) distance += manhattan_distance(j, i);
//             }
//         }
//     }
//     return distance;
// }

// int StaticEstimation::manhattan_distance(int to, int from) {
//     // TODO: 
//     return 0;
// }
//############################################################################//

int StaticEstimation::number_of_neighbors(std::string boardPosition, char c) {
    int neighborCount = 0;
    for (int i = 0; i < boardPosition.length(); ++i) {
        if (boardPosition[i] == c) {
            MoveGen moveGen;
            int* ip = moveGen.neighbors(i);
            for (int j = 1; j < ip[0]; ++j)
                if (boardPosition[ip[j]] == 'x' || boardPosition[ip[j]] == c) 
                    neighborCount++;
        }
    }
    return neighborCount;
}

int StaticEstimation::number_of_pieces(std::string boardPosition, char c) {

    // COUNTER
    //------------------------------------------------------------------------//
    int numOfPieces = 0;

    // COUNT NUMBER OF PIECES
    //------------------------------------------------------------------------//
    for (int i = 0; i < boardPosition.length(); ++i) 
        if (boardPosition[i] == c) ++numOfPieces;
    
    // RETURN THE RESULT
    //------------------------------------------------------------------------//
    return numOfPieces;
}
//============================================================================//

// GETTERS AND SETTERS
//============================================================================//
std::vector<std::string> StaticEstimation::get_positions() {
    return positions;
} // get_positions()

int StaticEstimation::get_max_estimation() {
    return maxEstimation;
} // get_max_estimation()

int StaticEstimation::get_min_estimation() {
    return minEstimation;
} // get_min_estimation()

void StaticEstimation::set_postions(std::vector<std::string> positions) {
    this->positions = positions;
} // set_postions()
//============================================================================//