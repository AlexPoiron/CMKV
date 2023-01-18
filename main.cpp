#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <math.h>

#include "tetravex.hpp"
#include "solver.hpp"

// argc[0] = in.txt
// ligne = 1 piece / si arobase -> fixed = 1
// compter nombre de ligne. si sqrt(lignes) = int ok else wrong size
// good format : line /n line /n

int main(int argc, char **argv)
{
    // command line ./a.out in.txt out.txt

    if (argc != 3)
    {
        throw std::invalid_argument("Your command line has to be : command line ./a.out in.txt out.txt\n");
    }

    Solver solver(0.1, 100, 0.99999);

    std::fstream infile(argv[1]);
    std::fstream outfile(argv[2]);

    Tetravex tetravex = to_tetravex(infile);
    solver.solve(tetravex);
    std::cout << tetravex;

    infile.close();
    outfile.close();
    return 0;
}