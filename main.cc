#include "tetravex.hh"
#include "solver.hh"

/**
 * @brief Main function of the project
*/
int main(int argc, char **argv)
{
    // Command line: ./a.out in.txt out.txt
    if (argc != 3)
    {
        throw std::invalid_argument("Your command line has to be : command line ./a.out in.txt out.txt\n");
    }

    // Hyperparameter for our solver
    float TEMP_MIN = 0.8;
    float TEMP_MAX = 10.0;
    float LAMBDA = 0.0001;

    // Create a Solver object 
    Solver solver(TEMP_MIN, TEMP_MAX, LAMBDA);

    // File stream for the input and output file
    std::fstream infile(argv[1]);
    std::fstream outfile(argv[2], std::fstream::out);

    // Create a Tetravex object from the input file
    bool fixed = true;
    Tetravex tetravex = to_tetravex(infile, fixed);
    
    // Solving the Tetravex and print the solution in the terminal
    solver.solve(tetravex);
    std::cout << tetravex;

    //Write the solution in the right format in the output file
    outfile << tetravex;

    //Close both file stream
    infile.close();
    outfile.close();

    return 0;
}