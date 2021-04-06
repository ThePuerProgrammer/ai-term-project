//============================================================================//
// * JESSE RANKINS
// * UCO COMPUTER SCIENCE 2021
// * CONCEPTS OF AI - TERM PROJECT
// * STATE NODE CLASS IMPLEMENTATION FILE 
// * TREE BUILDING NODE ELEMENT FOR GAME BOARD STATES
//============================================================================//

// INCLUDES
//============================================================================//
#include "StateNode.h"
#include <iostream>
//============================================================================//

// CONSTRUCTORS/DESTRUCTOR
//============================================================================//
StateNode::StateNode(int height, int depth) {
    this->height = height;
    this->depth = depth;
}

StateNode::StateNode(
    std::vector<std::string> boardStates, int height, int depth
    ) {
    this->boardStates = boardStates;
    this->height = height;
    this->depth = depth;
}

StateNode::~StateNode() {
    for (int i = 0; i < childNodes.size(); ++i)
        if (childNodes[i]) delete childNodes[i];
}
//============================================================================//

// PUBLIC FUNCTIONS
//============================================================================//
void StateNode::add_child(std::vector<std::string> childBoardStates) {
    childNodes.push_back(new StateNode(childBoardStates, height, depth + 1));
}
//============================================================================//

// GETTERS/SETTERS
//============================================================================//
std::vector<StateNode*> StateNode::get_child_nodes() {
    return childNodes;
}

std::vector<std::string> StateNode::get_board_states() {
    return boardStates;
}

int StateNode::get_depth() {
    return depth;
}

void StateNode::set_child_nodes(std::vector<StateNode*> childNodes) {
    this->childNodes = childNodes;
}

void StateNode::set_board_states(std::vector<std::string> boardStates) {
    this->boardStates = boardStates;
}
//============================================================================//