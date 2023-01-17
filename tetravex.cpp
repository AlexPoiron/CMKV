#include "tetravex.hpp"

#include <stdexcept>
using namespace std;

Tetravex::Tetravex(int width, int height)
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

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex)
{
	o << " ";
	for (int i = 0; i < tetravex.get_width(); ++i)
			o << "----------";
		o << "-\n";

	for (int i = 0; i < tetravex.get_height(); ++i)
	{
		o << "| ";
		for (int j = 0; j < tetravex.get_width(); ++j)
			o << " -------  ";
		o << "|\n";

		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < tetravex.get_width(); ++k)
			{
				if (k == 0)
				{
					o << "| ";
				}
				Piece p = tetravex.get_pieces()[i * tetravex.get_width() + k];
				if (j == 1)
                {
					o << "| " << p.values[1] << "   " << p.values[2] << " |";
                }
				else if (j == 2)
				{
					o << "|   " << p.values[3] << "   |";
				}
				else
				{
					o << "|   " << p.values[0] << "   |";
				}
				o << " ";
				if (k == tetravex.get_width() - 1)
				{
					o << "|";
				}
			}
			o << "\n";
		}

		o << "| ";
		for (int j = 0; j < tetravex.get_width(); ++j)
			o << " -------  ";
		o << "|\n";
	}

	o << " ";
	for (int i = 0; i < tetravex.get_width(); ++i)
			o << "----------";
		o << "-\n";
	
	return o;
}