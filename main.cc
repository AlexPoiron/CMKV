#include "tetravex.hh"
#include "solver.hh"

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

    Solver solver(0.8, 10, 0.9999);

    std::fstream infile(argv[1]);
    std::fstream outfile(argv[2], std::fstream::out);

    bool fixed = true;
    Tetravex tetravex = to_tetravex(infile, fixed);
    
    solver.solve(tetravex);
    std::cout << tetravex;
    outfile << tetravex;

    infile.close();
    outfile.close();
    return 0;
}