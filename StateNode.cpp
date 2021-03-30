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
void StateNode::addChild(std::vector<std::string> childBoardStates) {
    childNodes.push_back(new StateNode(childBoardStates, height, depth + 1));
}
//============================================================================//

// GETTERS/SETTERS
//============================================================================//
std::vector<StateNode*> StateNode::getChildNodes() {
    return childNodes;
}

std::vector<std::string> StateNode::getBoardStates() {
    return boardStates;
}

int StateNode::getDepth() {
    return depth;
}

void StateNode::setChildNodes(std::vector<StateNode*> childNodes) {
    this->childNodes = childNodes;
}

void StateNode::setBoardStates(std::vector<std::string> boardStates) {
    this->boardStates = boardStates;
}
//============================================================================//