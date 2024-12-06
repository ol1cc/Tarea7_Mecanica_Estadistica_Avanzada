#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include "simulation_parameters.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Parámetros de la simulación
    double beta = 0.2;
    double kappa = 1e-4;
    double dt = 0.01;
    double total_time = 100;
    SimulationParameters params(beta, kappa, dt, total_time); // Inicialización de parámetros

    // Variables de la simulación
    double g = 1.5;
    bool add_noise = true;
    Intensity intensity(1);  // Condición inicial

    // Generación del archivo de resultados
    std::ostringstream file_name;
    file_name << "data/intensity/int_n=" << ([](bool t) { return t ? "true" : "false"; } (add_noise))  << "_g=" << g << ".txt";
    std::ofstream file(file_name.str());
    std::cout << file_name.str() << std::endl;
    
    for(int i = 0; i <= params.steps; ++i) {
        double time_step = i * params.dt;
        file << time_step << "\t" << intensity.I << std::endl;

        // Actualización de la intensidad
        double new_I = euler_update(intensity.I, g, params, add_noise, gen);
        intensity.update_averages(new_I);
    }

    // Cálculo de promedios
    double av_I = intensity.sum_I / params.steps;
    double av_I2 = intensity.sum_I2 / params.steps;

    std::cout << "Data saved to '" << file_name.str() << "'" << std::endl;
    file.close();

    // Guardar promedios
    std::ostringstream average_file_name;
    average_file_name << "data/averages/av_g=" << ([](bool t) { return t ? "true" : "false"; } (add_noise)) << ".txt";
    std::ofstream average_file(average_file_name.str());
    average_file << "Averages for g = " << g << std::endl;
    average_file << "===============" << std::endl;
    average_file << "〈I〉= " << av_I << "\n〈I²〉= " << av_I << "\nFluctuation: "<< av_I2 - av_I * av_I;
    
    std::cout << "Averages saved to '" << average_file_name.str() << "'" << std::endl;
    return 0;
}