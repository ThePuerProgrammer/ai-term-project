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
    std::vector<std::string> generate_add();
    std::vector<std::string> generate_move();
    std::vector<std::string> generate_moves_opening();
    std::vector<std::string> generate_hopping();
    std::vector<std::string> generate_moves_midgame_endgame();
    int* neighbors(const int&);
    void generate_remove();
    bool close_mill(const int&);
    //------------------------------------------------------------------------//

    // GETTERS AND SETTERS
    //------------------------------------------------------------------------//
    std::vector<std::string> get_board_states();
    std::string get_input_board_state();
    std::string get_copy_board_state();

    void set_board_states(std::vector<std::string> boardStates);
    void set_input_board_state(std::string inputBoardState);
    void set_copy_board_state(std::string copyBoardState);
    //------------------------------------------------------------------------//
};
//============================================================================//
#endif