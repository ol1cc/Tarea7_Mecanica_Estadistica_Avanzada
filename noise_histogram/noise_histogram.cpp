#include <random>
#include <cmath>
#include <fstream>

int main(){
    double kappa = 1e-4;
    double dt = 0.01;
    double total_time = 100;

    double steps = total_time / dt;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(0, std::sqrt(kappa / dt));

    std::ofstream file("noise_counts.txt");

    for(int i = 0; i < steps; ++i){
        double f = noise(gen);
        file << i * dt << "\t" << f << std::endl;
    }

    file.close();

    return 0;
}