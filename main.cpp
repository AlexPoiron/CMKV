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

Tetravex to_tetravex(std::fstream& infile)
{
    if (!infile){
        std::cerr << "File not found\n";
    }

    std::vector<Piece> pieces;
    
    int minimal_length = 4;
    int maximal_length = 6; 

    std::string line;
    int count_line = 0;
    
    while(std::getline(infile, line))
    {
        if (line.length() < minimal_length || line.length() > maximal_length+1){
            throw std::invalid_argument("Input file with wrong format !\n");
        }
        
        Piece new_piece;

        //Check if there are 4 int and append them to our values list.
        for (int i=0; i < minimal_length; i++)
        {
            const char c = line[i];
            if ('0' > c || c > '9')
            {
                throw std::invalid_argument("Input file with wrong format, numeric check failed\n.");
            }

            int value = c - '0';
            new_piece.values[i] = value;
        }

        //End of line
        if (line.length() == 5 || line.length() == 4)
        {
            new_piece.fixed = 0;
        }
        else if (line.find('@') < line.length() || line.find(' ') < line.length())
        {
            new_piece.fixed = 1;
        }
        else
        {
            throw std::invalid_argument("Input file with wrong format\n");
        }
        pieces.push_back(new_piece);
        count_line++;
    }

    // Check size of the tetravex (2x2 to 6x6)
    if (sqrt(count_line) != 2 && sqrt(count_line) != 3 && sqrt(count_line) != 4 && sqrt(count_line) != 5 && sqrt(count_line) != 6)
    {
        throw std::invalid_argument("Wrong size in the input file.\n");
    }

    int dims = sqrt(count_line);

    Tetravex tetravex = Tetravex(dims, dims);
    tetravex.set_pieces(pieces);

    return tetravex;
}

int main(int argc, char** argv)
{
    //command line ./a.out in.txt out.txt
    if(argc != 3){
        throw std::invalid_argument("Your command line has to be : command line ./a.out in.txt out.txt\n");
    }
    
    std::fstream infile (argv[1]);
    std::fstream outfile (argv[2]);

    Tetravex tetravex = to_tetravex(infile);    
    Solver solver(1, 4, 0.99);

    solver.solve(tetravex);
    std::cout << tetravex;

    return 0;
}