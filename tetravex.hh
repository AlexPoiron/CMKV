#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <numeric>
#include <cstring>
#include <math.h>


// Position of our pieces following the order North, West, Est and South
// Useful later to get the correct index
#define N 0
#define W 1
#define E 2
#define S 3

/**
 * @brief Definition of a piece object. A piece is a simple object containing an array
 * of 4 numeric values. We added a boolean value that correspond if the piece is
 * fixed or not.
*/
struct Piece
{
    int values[4];
    int fixed;
};

/**
 * @brief Definition of the Tetravex class.
*/
class Tetravex
{
public:
    // Constructor
    Tetravex(int width, int height);

    // Setter
    void set_pieces(std::vector<Piece> pieces);

    // Getters
    std::vector<Piece> get_pieces() const;
    int get_width() const;
    int get_height() const;

private:
    // Attributes
    int width;
    int height;
    int nb_values;
    std::vector<Piece> pieces;
};

// Useful methods on tetravex object
//Redirection ones for pretty print and write in the output file.
std::ostream &operator<<(std::ostream &o, const Tetravex &tetravex);
std::fstream &operator<<(std::fstream &file, Tetravex &tetravex);

// Parsing method from the input file
Tetravex to_tetravex(std::fstream &infile, bool &fixed);
