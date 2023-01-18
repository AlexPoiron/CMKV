#pragma once

#include "tetravex.hh"
#include <random>

/**
 * @brief Definition of the Solver class.
*/
class Solver
{
    public:
        // Constructor
        Solver(float temperature_min, float temperature_max, float lambda);
        
        // Methods
        int compute_total_score(std::vector<int> scores);
        std::vector<int> compute_pieces_scores(std::vector<Piece> pieces, int width, int height);
        void compute_pieces_distributions(std::vector<int> pieces_scores, int nb_pieces);
        
        bool accept(int current_score, int new_score, float temperature);
        void solve(Tetravex& game);
        
    private:
        // Attributes
        float temperature_min;
        float temperature_max;
        float lambda;

        std::mt19937 generator;
        std::uniform_real_distribution<double> accept_distribution;
        std::discrete_distribution<int> pieces_distribution;
 

};

// Method to swap pieces to solve the tetravex
void swap_pieces(std::vector<Piece> *pieces, int piece1, int piece2);
