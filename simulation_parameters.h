#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H

#include <random>
#include <cmath>

// Estructura que guarda los parámetros de la simulación
struct SimulationParameters {
    double beta;
    double kappa;
    double dt;
    double steps;
    double A;

    SimulationParameters(double beta, double kappa, double dt, double total_time);
};

// Clase que maneja la intensidad
class Intensity {
public:
    double I;
    double I2;
    double sum_I;
    double sum_I2;

    Intensity(double I);
    void update_averages(double new_I);
};

// Función que realiza una actualización usando el método de Euler
double euler_update(double I, double g, const SimulationParameters& params, bool add_noise, std::mt19937& gen);

#endif