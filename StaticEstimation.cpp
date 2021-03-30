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
//============================================================================//

// STATIC IMPLEMENTATION
//============================================================================//
int StaticEstimation::positionsEvaluated = 0;
//============================================================================//

// CONSTRUCTORS
//============================================================================//
StaticEstimation::StaticEstimation() {} // StaticEstimation()

StaticEstimation::StaticEstimation(std::vector<std::string> positions) {
    this->positions = positions;
} // StaticEstimation(std::vector<std::string>)
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
void StaticEstimation::estimateMidgame() {

    // VARIABLE SET TO INT_MIN WILL TRACE BEST ESTIMATION
    //------------------------------------------------------------------------//
    int bestimation = -2147483648;

    // FOR EVERY BOARD POSITION IN POSITIONS
    //------------------------------------------------------------------------//
    for (int i = 0; i < positions.size(); ++i) {
        ++positionsEvaluated;

    }
    //------------------------------------------------------------------------//

    // SET THE FINAL BEST ESTIMATION FOR GETTER
    //------------------------------------------------------------------------//
    bestEstimation = bestimation;
} // estimateAll()

void StaticEstimation::estimateOpening() {

    // VARIABLE SET TO INT_MIN WILL TRACE BEST ESTIMATION
    //------------------------------------------------------------------------//
    int bestimation = -2147483648;

    // FOR EVERY BOARD POSITION IN POSITIONS
    //------------------------------------------------------------------------//
    for (int i = 0; i < positions.size(); ++i) {

        ++positionsEvaluated;
        
        // GET WHITE COUNT MINUS BLACK COUNT
        //--------------------------------------------------------------------//
        int whiteCount = numberOfWhitePieces(positions[i]);
        int blackCount = numberOfBlackPieces(positions[i]);
        int whiteMinusBlack = whiteCount - blackCount;

        // ADD TO HASHMAP
        //--------------------------------------------------------------------//
        estimationsMap.insert(std::make_pair(whiteMinusBlack, i));

        // UPDATE BEST ESTIMATION IF NEEDED
        //--------------------------------------------------------------------//
        if (whiteMinusBlack > bestimation)
            bestimation = whiteMinusBlack;
    }
    //------------------------------------------------------------------------//

    // SET THE FINAL BEST ESTIMATION FOR GETTER
    //------------------------------------------------------------------------//
    bestEstimation = bestimation;
}

int StaticEstimation::numberOfWhitePieces(std::string boardPosition) {

    // COUNTER
    //------------------------------------------------------------------------//
    int numOfWhitePieces = 0;

    // COUNT NUMBER OF WHITE PIECES
    //------------------------------------------------------------------------//
    for (int i = 0; i < boardPosition.length(); ++i) 
        if (boardPosition[i] == 'W') ++numOfWhitePieces;
    
    // RETURN THE RESULT
    //------------------------------------------------------------------------//
    return numOfWhitePieces;
}

int StaticEstimation::numberOfBlackPieces(std::string boardPosition) {

    // COUNTER
    //------------------------------------------------------------------------//
    int numOfBlackPieces = 0;

    // COUNT NUMBER OF BLACK PIECES
    //------------------------------------------------------------------------//
    for (int i = 0; i < boardPosition.length(); ++i) 
        if (boardPosition[i] == 'B') ++numOfBlackPieces;
    
    // RETURN THE RESULT
    //------------------------------------------------------------------------//
    return numOfBlackPieces;
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

int StaticEstimation::getBestEstimation() {
    return bestEstimation;
} // getBestEstimation()

void StaticEstimation::setPositions(std::vector<std::string> positions) {
    this->positions = positions;
} // setPositions()

void StaticEstimation::setEstimationsMap(std::unordered_map<int, int> eMap) {
    this->estimationsMap = eMap;
} // setEstimationsMap()
//============================================================================//