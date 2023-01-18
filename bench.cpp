#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <chrono>

#include "tetravex.hpp"
#include "solver.hpp"

// argc[0] = in.txt
// ligne = 1 piece / si arobase -> fixed = 1
// compter nombre de ligne. si sqrt(lignes) = int ok else wrong size
// good format : line /n line /n

std::vector<std::string> search_data(char size)
{
    std::vector<std::string> grids;

    DIR *directory = opendir("data/input");

    struct dirent *entry;
    while (NULL != (entry = readdir(directory)))
    {
        if (entry->d_name[1] == size)
        {
            std::string filename = entry->d_name;
            filename = "data/input/" + filename;
            grids.push_back(filename);
        }
    }
    return grids;
}

std::vector<Tetravex> construct_tetravexes(std::vector<std::string> grids, int turns, bool fixed) {
    std::vector<Tetravex> tetravexes;

    for (int i = 0; i < turns; i++)
    {
        for (int j = 0; j < grids.size(); j++)
        {
            std::fstream infile(grids[j]);

            bool fixed_grid = false;

            Tetravex tetravex = to_tetravex(infile, fixed_grid);

            if (!fixed || fixed_grid)
            {
                std::cout << grids[j] << std::endl;
                tetravexes.push_back(tetravex);
            }

            infile.close();
        }
    }

    return tetravexes;
}


void bench(std::vector<Tetravex> tetravexes, Solver solver) {
    using namespace std::chrono;
    
    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < tetravexes.size(); i++)
    {
        solver.solve(tetravexes[i]);
        //std::cout << tetravexes[i] << std::endl;
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> duration = duration_cast<milliseconds>(end - start);
    
    std::cout << "Total bench time (" << tetravexes.size() << " tetravexes): " << duration.count() << " milliseconds" << std::endl;
}


int main(int argc, char **argv)
{
    // command line ./bench size


    if (argc != 4)
    {
        throw std::invalid_argument("Your command line has to be : command line ./bench grid_size turns\n");
    }

    int turns = atoi(argv[2]);
    bool fixed = atoi(argv[3]);

    std::vector<std::string> grids = search_data(argv[1][0]);

    if (grids.empty())
    {
        throw std::invalid_argument("Invalid size of grid for benchmark\n");
    }

    Solver solver(0.80, 15, 0.9999);


    std::vector<Tetravex> tetravexes = construct_tetravexes(grids, turns, fixed);

    std::cout << "Awaiting key press to start solving ..." << std::endl;
    getchar();

    bench(tetravexes, solver);

    return 0;
}