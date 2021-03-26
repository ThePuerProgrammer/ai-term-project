//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * DECLARATION FILE FOR A MOVE GENERATOR
//============================================================================//

// PREPROCESSORS
//============================================================================//
#ifndef MOVEGEN_H
#define MOVEGEN_H
//============================================================================//

// INCLUDES 
//============================================================================//
#include <vector>
#include <string>
//============================================================================//

// MOVEGEN
//============================================================================//
class MoveGen {
private:  
    // PRIVATE MEMBERS
    //------------------------------------------------------------------------//
    std::string inputBoardState; 
    std::string copyBoardState; 
    std::vector<std::string> boardStates;
    //------------------------------------------------------------------------//
public:  
    // CONSTRUCTORS
    //------------------------------------------------------------------------//
    MoveGen();
    MoveGen(std::string);
    //------------------------------------------------------------------------//

    // PUBLIC FUNCTIONS
    //------------------------------------------------------------------------//
    std::vector<std::string> generateAdd();
    std::vector<std::string> generateMove();
    std::vector<std::string> generateMovesOpening();
    std::vector<std::string> generateHopping();
    std::vector<std::string> generateMovesMidgameEndgame();
    int* neighbors(const int&);
    void generateRemove();
    bool closeMill(const int&);
    //------------------------------------------------------------------------//

    // GETTERS AND SETTERS
    //------------------------------------------------------------------------//
    std::vector<std::string> getBoardStates();
    std::string getInputBoardState();
    std::string getCopyBoardState();

    void setBoardStates(std::vector<std::string> boardStates);
    void setInputBoardState(std::string inputBoardState);
    void setCopyBoardState(std::string copyBoardState);
    //------------------------------------------------------------------------//
};
//============================================================================//
#endif