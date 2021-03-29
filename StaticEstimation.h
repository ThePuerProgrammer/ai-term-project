//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * STATIC ESTIMATION CLASS DECLARATION FILE 
// * EVALUATES A LIST OF GENERATED POSSIBILITIES FOR OPTIMAL OUTCOME
//============================================================================//

// PREPROCESSORS
//============================================================================//
#ifndef STATIC_ESTIMATION_H
#define STATIC_ESTIMATION_H
//============================================================================//

// INCLUDES
//============================================================================//
#include <string>
#include <vector>
#include <unordered_map>
//============================================================================//

// STATIC ESTIMATION
//============================================================================//
class StaticEstimation {
private:  
    // PRIVATE MEMBERS
    //------------------------------------------------------------------------//
    std::vector<std::string> positions;
    std::unordered_map<int, int> estimationsMap;
    int bestEstimation;
    //------------------------------------------------------------------------//
public:  
    // CONSTRUCTORS
    //------------------------------------------------------------------------//
    StaticEstimation();
    StaticEstimation(std::vector<std::string>);
    //------------------------------------------------------------------------//

    // PUBLIC FUNCTIONS
    //------------------------------------------------------------------------//
    void estimateMidgame();
    void estimateOpening();
    int numberOfBlackPieces(std::string);
    int numberOfWhitePieces(std::string);
    int numberOfBlackMoves();
    //------------------------------------------------------------------------//

    // GETTERS AND SETTERS
    //------------------------------------------------------------------------//
    std::vector<std::string> getPositions();
    std::unordered_map<int, int> getEstimationsMap();
    int getBestEstimation();

    void setPositions(std::vector<std::string>);
    void setEstimationsMap(std::unordered_map<int, int>);
    //------------------------------------------------------------------------//
}; // class StaticEstimation
//============================================================================//
#endif