#include "tetravex.hpp"

#include <stdexcept>
#include <string>
#include <numeric>
#include <cstring>
#include <math.h>
using namespace std;

Tetravex::Tetravex(int width, int height)
{
	if (width != height)
	{
		throw std::invalid_argument("Invalid size in the input file. \n");
	}
	this->width = width;
	this->height = height;
	this->nb_values = 4 * width * height;
	this->pieces = std::vector<Piece>(this->width * this->height);
	this->scores = std::vector<int>(this->width * this->height);
	compute_pieces_scores();
}

void Tetravex::set_pieces(std::vector<Piece> pieces)
{
	this->pieces = pieces;
	compute_pieces_scores();
}

void Tetravex::set_scores(std::vector<int> scores){
	this->scores = scores;
}

std::vector<int> Tetravex::get_scores() const{
	return this->scores;
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

int Tetravex::compute_total_score(){
	return std::accumulate(this->scores.begin(), this->scores.end(), 0);
}

void Tetravex::compute_pieces_scores(){
	int nb_pieces = this->width * this->height;
	
    for (int i = 0; i < nb_pieces; i++)
    {
		int score = 0;
        if (i - 1 >= 0 && this->pieces[i].values[W] == this->pieces[i - 1].values[E])
            score++;
        if (i - this->width >= 0 && this->pieces[i].values[N] == this->pieces[i - this->width].values[S])
            score++;
     	if (i + 1 < nb_pieces && this->pieces[i].values[E] == this->pieces[i + 1].values[W])
            score++;
        if (i + this->width < nb_pieces && this->pieces[i].values[S] == this->pieces[i + this->width].values[N])
            score++;

		this->scores[i] = score;
    }
}

std::ostream &operator<<(std::ostream &o, const Tetravex &tetravex)
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

std::fstream &operator<<(std::fstream &file, Tetravex &tetravex)
{
	std::vector<Piece> pieces = tetravex.get_pieces();
	for(int i = 0; i < pieces.size(); ++i)
	{
		Piece piece = pieces[i];
		for (int i = 0; i < 4; ++i)
		{
			file << piece.values[i];
		}
		if (piece.fixed)
		{
			file << "  @\n";
		}
		file << '\n';
		
	}
	return file;

}

Tetravex to_tetravex(std::fstream &infile, bool &fixed)
{
	if (!infile)
	{
		std::cerr << "File not found\n";
	}

	std::vector<Piece> pieces;

	int minimal_length = 4;
	int maximal_length = 6;

	std::string line;
	int count_line = 0;

	while (std::getline(infile, line))
	{
		if (line.length() < minimal_length || line.length() > maximal_length + 1)
		{
			throw std::invalid_argument("Input file with wrong format !\n");
		}

		Piece new_piece;

		// Check if there are 4 int and append them to our values list.
		for (int i = 0; i < minimal_length; i++)
		{
			const char c = line[i];
			if ('0' > c || c > '9')
			{
				throw std::invalid_argument("Input file with wrong format, numeric check failed\n.");
			}

			int value = c - '0';
			new_piece.values[i] = value;
		}

		// End of line
		if (line.length() == 5 || line.length() == 4)
		{
			new_piece.fixed = 0;
		}
		else if (line.find('@') < line.length() || line.find(' ') < line.length())
		{
			new_piece.fixed = 1;
			fixed = true;
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