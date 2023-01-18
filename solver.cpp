#include "solver.hpp"

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
    this->distribution = std::uniform_real_distribution<double>(0, 1);
}

int Solver::compute_score(std::vector<Piece> *pieces, int nb_pieces, int width)
{
    int score = 0;

    for (int i = 0; i < nb_pieces; i++)
    {
        if (i + 1 < nb_pieces && (*pieces)[i].values[E] == (*pieces)[i + 1].values[W])
            score++;
        if (i + width < nb_pieces && (*pieces)[i].values[S] == (*pieces)[i + width].values[N])
            score++;
    }

    return score;
}

bool Solver::accept(int current_score, int new_score, float temperature)
{
    int delta = current_score - new_score;

    if (delta < 0)
        return true;

    float p = exp(-delta / temperature);

    float a = this->distribution(this->generator);

    if (p > a)
        return true;

    return false;
}

void swap_pieces(std::vector<Piece> *pieces, int piece1, int piece2)
{
    Piece tmp = (*pieces)[piece1];
    (*pieces)[piece1] = (*pieces)[piece2];
    (*pieces)[piece2] = tmp;
}

void Solver::solve(Tetravex &game)
{
    std::vector<Piece> pieces = game.get_pieces();

    int width = game.get_width();
    int height = game.get_height();

    int max_score = ((width - 1) * height) + ((height - 1) * width);

    int nb_pieces = width * height;

    int current_score = compute_score(&pieces, nb_pieces, width);

    float temperature = temperature_max;
    int iterations = 0;

    while (current_score != max_score)
    {

        int piece1 = 0;
        int piece2 = 0;

        do
        {
            piece1 = floor(this->distribution(this->generator) * (nb_pieces));
            piece2 = floor(this->distribution(this->generator) * (nb_pieces));
        } while (piece1 == piece2 || pieces[piece1].fixed || pieces[piece2].fixed);


        swap_pieces(&pieces, piece1, piece2);

        int new_score = compute_score(&pieces, nb_pieces, width);

        if (accept(current_score, new_score, temperature))
        {
            game.set_pieces(pieces);
            current_score = new_score;
        }

        printf("Score : %d, Temperature : %.6f\n", current_score, temperature);

        pieces = game.get_pieces();

        if (temperature > temperature_min)
        {
            //temperature = temperature_max / (1 + lambda * iterations);
            temperature *= lambda;
        }

        iterations++;
    }
    printf("Iterations : %d\n", iterations);
}
