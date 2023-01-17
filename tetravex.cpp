#include "tetravex.hpp"

#include <stdexcept>
using namespace std;

Tetravex::Tetravex(int width, int height, int nb_values)
{
	if (width != height)
	{
		throw std::invalid_argument("Invalid size in the input file. \n");
	}
	this->width = width;
	this->height = height;
	this->nb_values = 4*width*height;
	this->pieces = std::vector<Piece>(this->width * this->height);
}

void Tetravex::set_pieces(std::vector<Piece> pieces)
{
	this->pieces = pieces;
}

std::vector<Piece> Tetravex::get_pieces() const
{
	return this->pieces;
}

int Tetravex::get_width() const
{
	return this->width;
}

int Tetravex::get_height() const
{
	return this->height;
}