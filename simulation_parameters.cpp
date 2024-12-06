#include "simulation_parameters.h"

// Definición del constructor de SimulationParameters
SimulationParameters::SimulationParameters(double beta, double kappa, double dt, double total_time)
    : beta(beta), kappa(kappa), dt(dt), steps(total_time / dt), A(std::sqrt(kappa / dt)) {}

// Definición del constructor de Intensity
Intensity::Intensity(double I)
    : I(I), I2(I * I), sum_I(I), sum_I2(I * I) {}

// Definición de la función para actualizar promedios en Intensity
void Intensity::update_averages(double new_I) {
    I = new_I;
    I2 = I * I;
    sum_I += I;
    sum_I2 += I2;
}

// Definición de la función euler_update
double euler_update(double I, double g, const SimulationParameters& params, bool add_noise, std::mt19937& gen) {
    std::normal_distribution<double> noise(0, params.A);
    double f = add_noise ? noise(gen) : 0.0;
    double new_I = I + params.dt * ((g - 1) * I - params.beta * I * I + f);
    return new_I > 0 ? new_I : 0;
}