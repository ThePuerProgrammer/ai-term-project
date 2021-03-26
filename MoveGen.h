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
    std::string inputBoardPosition; 
    std::string copyBoardPosition; 
    std::vector<std::string> boardPositions;
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
    int* neighbors(int&);
    void generateRemove();
    bool closeMill(int&);
    //------------------------------------------------------------------------//

    // GETTERS AND SETTERS
    //------------------------------------------------------------------------//
    std::vector<std::string> getBoardPositions();
    std::string getInputBoardPosition();
    std::string getCopyBoardPosition();

    void setBoardPositions(std::vector<std::string> boardPositions);
    void setInputBoardPosition(std::string inputBoardPosition);
    void setCopyBoardPosition(std::string copyBoardPosition);
    //------------------------------------------------------------------------//
};
//============================================================================//
#endif