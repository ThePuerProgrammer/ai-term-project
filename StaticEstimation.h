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
    int maxEstimation;
    int minEstimation;
    bool whitesTurn;
    //------------------------------------------------------------------------//
public:  
    // CONSTRUCTORS
    //------------------------------------------------------------------------//
    StaticEstimation();
    StaticEstimation(bool);
    StaticEstimation(std::vector<std::string>, bool);
    //------------------------------------------------------------------------//

    // PUBLIC STATIC VARIABLES
    //------------------------------------------------------------------------//
    static int positionsEvaluated;
    //------------------------------------------------------------------------//

    // PUBLIC FUNCTIONS
    //------------------------------------------------------------------------//
    void estimate_opening();
    int number_of_pieces(std::string, char);
    int number_of_neighbors(std::string, char);
    int distance_from_mills(std::string);
    int manhattan_distance(int, int);
    //------------------------------------------------------------------------//

    // GETTERS AND SETTERS
    //------------------------------------------------------------------------//
    std::vector<std::string> get_positions();
    int get_max_estimation();
    int get_min_estimation();
    bool get_whites_turn();

    void set_postions(std::vector<std::string>);
    void set_whites_turn(bool);
    //------------------------------------------------------------------------//
}; // class StaticEstimation
//============================================================================//
#endif