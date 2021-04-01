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
void StaticEstimation::estimateMidgame() {

    // VARIABLE SET TO INT_MIN WILL TRACE BEST ESTIMATION
    //------------------------------------------------------------------------//
    int bestimation = -2147483648;
    int worstimation = 2147483647;

    // FOR EVERY BOARD POSITION IN POSITIONS
    //------------------------------------------------------------------------//
    for (int i = 0; i < positions.size(); ++i) {
        ++positionsEvaluated;

    }
    //------------------------------------------------------------------------//

    // SET THE FINAL BEST ESTIMATION FOR GETTER
    //------------------------------------------------------------------------//
    maxEstimation = bestimation;
} // estimateAll()

void StaticEstimation::estimateOpening() {

    // VARIABLE SET TO INT_MIN WILL TRACE BEST ESTIMATION
    //------------------------------------------------------------------------//
    int bestimation = -2147483648;
    int worstimation = 2147483647;

    // FOR EVERY BOARD POSITION IN POSITIONS
    //------------------------------------------------------------------------//
    for (int i = 0; i < positions.size(); ++i) {

        ++positionsEvaluated;
        
        // GET WHITE COUNT MINUS BLACK COUNT
        //--------------------------------------------------------------------//
        int whiteCount = numberOfPieces(positions[i], 'W');
        int blackCount = numberOfPieces(positions[i], 'B');
        int whiteMinusBlack;
        if (whitesTurn) {
            whiteMinusBlack = whiteCount - blackCount;
            whiteMinusBlack += numberOfNeighbors(positions[i], 'W');
        } else {
            whiteMinusBlack = blackCount - whiteCount;
            whiteMinusBlack += numberOfNeighbors(positions[i], 'B');
        }

        // ADD TO HASHMAP
        //--------------------------------------------------------------------//
        estimationsMap.insert(std::make_pair(i, whiteMinusBlack));

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

int StaticEstimation::numberOfNeighbors(std::string boardPosition, char c) {
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

int StaticEstimation::numberOfPieces(std::string boardPosition, char c) {

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
std::vector<std::string> StaticEstimation::getPositions() {
    return positions;
} // getPositions()

std::unordered_map<int, int> StaticEstimation::getEstimationsMap() {
    return estimationsMap;
} // getEstimationsMap()

int StaticEstimation::getMaxEstimation() {
    return maxEstimation;
} // getMaxEstimation()

int StaticEstimation::getMinEstimation() {
    return minEstimation;
} // getMinEstimation()

void StaticEstimation::setPositions(std::vector<std::string> positions) {
    this->positions = positions;
} // setPositions()

void StaticEstimation::setEstimationsMap(std::unordered_map<int, int> eMap) {
    this->estimationsMap = eMap;
} // setEstimationsMap()
//============================================================================//