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
    void addChild(std::vector<std::string>);
    //------------------------------------------------------------------------//

    // GETTERS/SETTERS
    //------------------------------------------------------------------------//
    std::vector<StateNode*> getChildNodes();
    std::vector<std::string> getBoardStates();
    int getDepth();
    int getHeight();

    void setChildNodes(std::vector<StateNode*>);
    void setBoardStates(std::vector<std::string>);
    void setDepth(int);
    void setHeight(int);
    //------------------------------------------------------------------------//
};
//============================================================================//
#endif