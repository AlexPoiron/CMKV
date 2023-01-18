#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

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

    // Setter for pieces
    void set_pieces(std::vector<Piece> pieces);
    void set_scores(std::vector<int> scores);

    // Getters
    std::vector<int> get_scores() const;
    std::vector<Piece> get_pieces() const;
    int get_width() const;
    int get_height() const;

    //Compute score 
    int compute_total_score();

private:
    void compute_pieces_scores();
    int width;
    int height;
    int nb_values;
    std::vector<Piece> pieces;
    std::vector<int> scores;
};

std::ostream &operator<<(std::ostream &o, const Tetravex &tetravex);
std::fstream &operator<<(std::fstream &file, Tetravex &tetravex);
Tetravex to_tetravex(std::fstream &infile, bool &fixed);
