#pragma once
#include <stdlib.h>
#include <vector>
#include "math.h"
#include "tetravex.hpp"

class Solver
{
    public:
        // Constructor
        Solver(float temperature_min, float temperature_max, float lambda);
        int compute_score(std::vector<Piece>* pieces, int np_pieces, int width);

        void solve(Tetravex& game);
    private:
        float temperature_min;
        float temperature_max;
        float lambda;
};

