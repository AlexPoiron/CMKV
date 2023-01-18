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
#define N 0
#define W 1
#define E 2
#define S 3

struct Piece
{
    int values[4];
    int fixed;
};

class Tetravex
{
public:
    // Constructor
    Tetravex(int width, int height);

    // Setters
    void set_pieces(std::vector<Piece> pieces);

    // Getters
    std::vector<Piece> get_pieces() const;
    int get_width() const;
    int get_height() const;

private:
    int width;
    int height;
    int nb_values;
    std::vector<Piece> pieces;
};

std::ostream &operator<<(std::ostream &o, const Tetravex &tetravex);
std::fstream &operator<<(std::fstream &file, Tetravex &tetravex);
Tetravex to_tetravex(std::fstream &infile, bool &fixed);
