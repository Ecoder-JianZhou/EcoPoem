#include <iostream>
#include <cmath>

// Constants for the Farquhar model
const double Vcmax = 100.0;  // Maximum rate of carboxylation (umol m^-2 s^-1)
const double Jmax = 150.0;  // Maximum rate of electron transport (umol m^-2 s^-1)
const double Kc = 404.9;    // Michaelis constant for CO2 (umol mol^-1)
const double Ko = 278.4;    // Michaelis constant for O2 (mmol mol^-1)
const double O2 = 210.0;    // Ambient oxygen concentration (mmol mol^-1)
const double Gamma_star = 42.75; // CO2 compensation point in the absence of mitochondrial respiration (umol mol^-1)
const double Rd = 1.5;      // Day respiration (umol m^-2 s^-1)

// Function to calculate the Rubisco-limited assimilation rate
double calcAc(double Ci) {
    return Vcmax * (Ci - Gamma_star) / (Ci + Kc * (1 + O2 / Ko));
}

// Function to calculate the RuBP regeneration-limited assimilation rate
double calcAj(double Ci, double I) {
    double J = (I * Jmax) / (I + 2.0); // Simplified electron transport rate
    return J * (Ci - Gamma_star) / (4 * Ci + 8 * Gamma_star);
}

// Function to calculate the net photosynthetic rate
double calcAn(double Ci, double I) {
    // Calculate Ac (Rubisco-limited) and Aj (RuBP-limited)
    double Ac = calcAc(Ci);
    double Aj = calcAj(Ci, I);

    // Net assimilation rate (considering respiration)
    return std::min(Ac, Aj) - Rd;
}

int main() {
    // Input values for intercellular CO2 concentration (Ci) and light intensity (I)
    double Ci;
    double I;

    std::cout << "Enter intercellular CO2 concentration (Ci, umol mol^-1): ";
    std::cin >> Ci;
    std::cout << "Enter light intensity (I, umol m^-2 s^-1): ";
    std::cin >> I;

    // Calculate the net photosynthetic rate
    double An = calcAn(Ci, I);

    std::cout << "\nNet photosynthetic rate (An): " << An << " umol m^-2 s^-1\n";

    return 0;
}
