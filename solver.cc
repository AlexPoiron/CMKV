#include "solver.hh"

/**
 * @brief Constructor of the Solver class.
 * 
 * @param temperature_min Hyperparameter for the minimal temperature
 * @param temperature_max Hyperparameter for the maximal temperature
 * @param lambda Hyperparameter that is set around 1 (0.999...)
 * 
 * @return Initialize a Solver object 
*/
Solver::Solver(float temperature_min, float temperature_max, float lambda)
{
    if (temperature_min > temperature_max)
    {
        throw std::invalid_argument("Minimum temperature cannot be higher than maximum temperature\n");
    }
    this->temperature_min = temperature_min;
    this->temperature_max = temperature_max;
    this->lambda = lambda;

    std::random_device rd;
    this->generator = std::mt19937(rd());
    this->accept_distribution = std::uniform_real_distribution<double>(0, 1);
}

/**
 * @brief Compute a weighted discrete distribution on each piece according to their score
 * 
 * @param pieces_scores The scores
 * @param nb_pieces Total number of pieces
*/
void Solver::compute_pieces_distributions(std::vector<int> pieces_scores, int nb_pieces) {

    std::vector<float> weights(nb_pieces);

    for (int i = 0; i < nb_pieces; i++) {
        weights[i] = 1 / ((pieces_scores[i] / 4) + 1);
    }
    
    this->pieces_distribution = std::discrete_distribution<int> (weights.begin(), weights.end());
}

/**
 * @brief Determine if we accept a recent swap between two pieces.
 * 
 * @param current_score Score before the swap
 * @param new_score Score after the swap
 * @param temperature The actual temperature
 * 
 * @return True or False
*/
bool Solver::accept(int current_score, int new_score, float temperature)
{
    int delta = current_score - new_score;

    if (delta < 0)
        return true;

    float p = exp(-delta / temperature);
    float a = this->accept_distribution(this->generator);

    if (p > a)
        return true;

    return false;
}

/**
 * @brief Swap two pieces
 * 
 * @param pieces The vector of pieces
 * @param piece1 Index of the first piece to swap
 * @param piece2 Index of the second piece top swap
*/
void swap_pieces(std::vector<Piece> *pieces, int piece1, int piece2)
{
    Piece tmp = (*pieces)[piece1];
    (*pieces)[piece1] = (*pieces)[piece2];
    (*pieces)[piece2] = tmp;
}

/**
 * @brief Compute the total score for all the pieces
 * 
 * @param scores Vector containing all the scores
 * 
 * @return The sum of these scores
*/
int Solver::compute_total_score(std::vector<int> scores){
    int total = 0;
    for (int i = 0; i < scores.size(); i++) {
        total += scores[i];
    }
	return total;
}

/**
 * @brief Compute for each piece its score following its placement and the connections in the game
 * 
 * @param pieces The vector of pieces
 * @param width First dimension of the tetravex board
 * @param height Second dimension of the tetravex board
 * 
 * @return A vector containing all the computed scores
*/
std::vector<int> Solver::compute_pieces_scores(std::vector<Piece> pieces, int width, int height){
	int nb_pieces = width * height;
    std::vector<int> scores(nb_pieces);

    for (int i = 0; i < nb_pieces; i++)
    {
		int score = 0;
        // Check for horizontal connection for both possibilities
        if (i - 1 >= 0 && i % width != 0 && pieces[i].values[W] == pieces[i - 1].values[E])
            score++;
        if (i + width < nb_pieces && pieces[i].values[S] == pieces[i + width].values[N])
            score++;

        // Check for vertical connection for both possibilites
        if (i - width >= 0 && pieces[i].values[N] == pieces[i - width].values[S])
            score++;
     	if (i + 1 < nb_pieces && i % width != width - 1 && pieces[i].values[E] == pieces[i + 1].values[W])
            score++;
        
		scores[i] = score;
    }
    return scores;
}

/**
 * @brief Main function where we solve our Tetravex following a Metropolis-Hastings with simulated annealing.
 * 
 * @param game Our Tetravex object
*/
void Solver::solve(Tetravex &game)
{
    std::vector<Piece> pieces = game.get_pieces();
    int width = game.get_width();
    int height = game.get_height();

    int max_score = (((width - 1) * height) + ((height - 1) * width)) * 2;
    int nb_pieces = width * height;

    std::vector<int> current_pieces_scores = compute_pieces_scores(pieces, width, height);
    int current_score = compute_total_score(current_pieces_scores);

    compute_pieces_distributions(current_pieces_scores, nb_pieces);

    float temperature = temperature_max;
    int iterations = 0;

    while (current_score != max_score && iterations < 100000000)
    {
        int piece1 = 0;
        int piece2 = 0;

        do
        {
            piece1 = this->pieces_distribution(this->generator);
            piece2 = this->pieces_distribution(this->generator);
        } while (piece1 == piece2 || pieces[piece1].fixed || pieces[piece2].fixed);

        compute_total_score(current_pieces_scores);
        swap_pieces(&pieces, piece1, piece2);
        
        std::vector<int> new_pieces_scores = compute_pieces_scores(pieces, width, height);
        int new_score = compute_total_score(new_pieces_scores);


        if (accept(current_score, new_score, temperature))
        {
            game.set_pieces(pieces);
            compute_pieces_distributions(new_pieces_scores, nb_pieces);
            current_pieces_scores = new_pieces_scores;
            current_score = new_score;
        }
        //printf("Score : %d, Temperature : %.6f\n", current_score, temperature);

        pieces = game.get_pieces();

        // We use a multiplicative monotonic cooling to decrease our temperature. We use precisely the linear one.
        // We follow this formula : Tk = T_max / (1 + lambda*k) with lambda > 0 anf k : number of iterations
        if (temperature > temperature_min)
        {
            temperature = temperature_max / (1 + lambda * iterations);
        }

        iterations++;
    }
    //printf("Iterations : %d\n", iterations);
}




