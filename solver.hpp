#pragma once
#include <stdlib.h>
#include <random>
#include <vector>
#include "math.h"
#include "tetravex.hpp"

class Solver
{
    public:
        // Constructor
        Solver(float temperature_min, float temperature_max, float lambda);
        int compute_score(std::vector<Piece>* pieces, int np_pieces, int width);
        bool accept(int current_score, int new_score, float temperature);
        void solve(Tetravex& game);

    private:
        float temperature_min;
        float temperature_max;
        float lambda;

        std::mt19937 generator;
        std::uniform_real_distribution<double> distribution;
 

};

