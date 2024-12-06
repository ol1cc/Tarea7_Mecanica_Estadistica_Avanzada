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
    double g = 0.75;
    bool add_noise = true;
    Intensity intensity(1);  // Condición inicial


    bool save_singular_g = false;
    if(save_singular_g){
        // Generación del archivo de resultados
        std::ostringstream file_name;
        file_name << "data/intensity/int_n=" << ([](bool t) { return t ? "true" : "false"; } (add_noise))  << "_g=" << g << ".txt";
        std::ofstream file(file_name.str());
    
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
        average_file_name << "data/averages/noise=" << ([](bool t) { return t ? "true" : "false"; } (add_noise)) << "_av_g=" << g << ".txt";
        std::ofstream average_file(average_file_name.str());
        average_file << "Averages for g = " << g << std::endl;
        average_file << "===============" << std::endl;
        average_file << "〈I〉= " << av_I << "\n〈I²〉= " << av_I << "\nFluctuation: "<< av_I2 - av_I * av_I;
        average_file.close();
        std::cout << "Averages saved to '" << average_file_name.str() << "'" << std::endl;
    }
    // Datos variando g
    bool g_series = true;
    if(g_series){
        double dg = 0.01;
        std::ofstream gvar("data/gvar/gvar.txt");
        for(double gs = 0; gs <= 2; gs += dg){
            Intensity temporal_intensity(1); // Cond. inicial
            for(int i = 0; i <= params.steps; ++i) {
                double new_I = euler_update(temporal_intensity.I, gs, params, add_noise, gen);
                temporal_intensity.update_averages(new_I);
            }
            double temp_av = temporal_intensity.sum_I / params.steps;
            double temp_av_sq = temporal_intensity.sum_I2 / params.steps;
            gvar << gs << "\t" << temp_av << "\t" << temp_av_sq - temp_av * temp_av << std::endl;
        }
    gvar.close();
    }

    return 0;
}