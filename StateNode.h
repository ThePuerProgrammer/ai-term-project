//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * STATE NODE CLASS DECLARATION FILE 
// * TREE BUILDING NODE ELEMENT FOR GAME BOARD STATES
//============================================================================//

// PREPROCESSORS
//============================================================================//
#ifndef STATE_NODE_H
#define STATE_NODE_H
//============================================================================//

// INCLUDES
//============================================================================//
#include <string>
#include <vector>
//============================================================================//

// STATE NODE CLASS DECLARATION
//============================================================================//
class StateNode {
private:  
    // PRIVATE MEMBERS
    //------------------------------------------------------------------------//
    std::vector<StateNode*> childNodes;
    std::vector<std::string> boardStates;
    int depth;
    int height;
    //------------------------------------------------------------------------//
public:  
    // CONSTRUCTORS/DESTRUCTOR
    //------------------------------------------------------------------------//
    StateNode(int, int);
    StateNode(std::vector<std::string>, int, int);
    ~StateNode();
    //------------------------------------------------------------------------//

    // PUBLIC FUNCTIONS
    //------------------------------------------------------------------------//
    void add_child(std::vector<std::string>);
    //------------------------------------------------------------------------//

    // GETTERS/SETTERS
    //------------------------------------------------------------------------//
    std::vector<StateNode*> get_child_nodes();
    std::vector<std::string> get_board_states();
    int get_depth();
    int get_height();

    void set_child_nodes(std::vector<StateNode*>);
    void set_board_states(std::vector<std::string>);
    void set_depth(int);
    void set_height(int);
    //------------------------------------------------------------------------//
};
//============================================================================//
#endif