#pragma once
#include <stdlib.h>
#include <random>
#include <vector>
#include "math.h"
#include "tetravex.hh"

class Solver
{
    public:
        // Constructor
        Solver(float temperature_min, float temperature_max, float lambda);
        
        //Methods
        int compute_total_score(std::vector<int> scores);
        std::vector<int> compute_pieces_scores(std::vector<Piece> pieces, int width, int height);
        void compute_pieces_distributions(std::vector<int> pieces_scores, int nb_pieces);
        
        bool accept(int current_score, int new_score, float temperature);
        void solve(Tetravex& game);
        
    private:
        float temperature_min;
        float temperature_max;
        float lambda;

        std::mt19937 generator;
        std::uniform_real_distribution<double> accept_distribution;
        std::discrete_distribution<int> pieces_distribution;
 

};

void swap_pieces(std::vector<Piece> *pieces, int piece1, int piece2);
