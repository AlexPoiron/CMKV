#include "tetravex.hh"

/**
 * @brief Constructor of our Tetravex class.
 * 
 * @param width first dimension of the border
 * @param height Second dimension of the border
 * 
 * @return Initialize a Tetravex object with the given parameters
*/
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
}

/// Setter and Getters

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

/**
 * @brief Redirection operator for pretty print.
 * 
 * @param o The output stream where the Tetravex is printed. In this context, it's always in the terminal
 * @param tetravex Tetravex object
 * 
 * @return The output stream given
*/
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

/**
 * @brief Redirection operator to save our Tetravex solved in an output file.
 * 
 * @param file The file where we want to save our solution
 * @param tetravex Our tetravex object
 * 
 * @return the given file stream
*/
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

		file << '\n';
	}
	return file;
}

/**
 * @brief Parsing method where from an input file we create a Tetravex object
 * 
 * @param infile The file stream related to the input file
 * @param fixed Boolean value that we set to True if we have a fixed piece in the file
 * 
 * @return A Tetravex object corresponding to the given input file.
*/
Tetravex to_tetravex(std::fstream &infile, bool &fixed)
{
	if (!infile)
	{
		std::cerr << "File not found\n";
	}

	std::vector<Piece> pieces;

	// Constant values representing min & max number of chars in one line in our input file
	int MIN_LG = 5; // 4 values of a piece + \n 
	int MAX_LG = 7; // 4 values + ' ' + '@' + \n

	std::string line;
	int count_line = 0;

	// Getline to read line by line our input file
	while (std::getline(infile, line))
	{
		// Check that our line length corresponding the the right format : 4 < length < 8
		if (line.length() < MIN_LG - 1 || line.length() > MAX_LG)
		{
			throw std::invalid_argument("Input file with wrong format !\n");
		}

		Piece new_piece;

		// Check if there are 4 numbers in the first 4 chars and append them to our values list.
		for (int i = 0; i < MIN_LG - 1; i++)
		{
			const char c = line[i];
			if ('0' > c || c > '9')
			{
				throw std::invalid_argument("Input file with wrong format, numeric check failed.\n");
			}

			int value = c - '0';
			new_piece.values[i] = value;
		}

		// Check if the piece is fixed or not
		if (line.length() == MIN_LG || line.length() == MIN_LG - 1)
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
			throw std::invalid_argument("Input file with wrong format on the lines.\n");
		}
		// Add the piece in our vector
		pieces.push_back(new_piece);
		count_line++;
	}

	// Check size of the tetravex (2x2 to 6x6)
	if (sqrt(count_line) != 2 && sqrt(count_line) != 3 && sqrt(count_line) != 4 && sqrt(count_line) != 5 && sqrt(count_line) != 6)
	{
		throw std::invalid_argument("Wrong size of grid in the input file.\n");
	}

	// Creation of the tetravex object
	int dims = sqrt(count_line);
	Tetravex tetravex = Tetravex(dims, dims);
	tetravex.set_pieces(pieces);

	return tetravex;
}