
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

// GARCH(1,1) Parameters
const double omega = 0.00001;
const double alpha = 0.05;
const double beta = 0.94;

// Simulation Parameters
const int N = 1000000; // One million simulated returns
const double confidence_level = 0.01; // 1% VaR and ES

int main() {

    vector<double> returns(N);
    vector<double> sigma2(N); // Conditional variance

    // Random number generation setup
    mt19937 gen(42);  // Fixed seed for replicability
    normal_distribution<> normal(0.0, 1.0);

    // Initial values
    sigma2[0] = omega / (1 - alpha - beta); // Unconditional variance
    returns[0] = sqrt(sigma2[0]) * normal(gen);

    // Simulate GARCH(1,1) returns
    for (size_t t = 1; t < N; ++t) {
        sigma2[t] = omega + alpha * pow(returns[t - 1], 2) + beta * sigma2[t - 1];
        double sigma_t = sqrt(sigma2[t]);
        returns[t] = sigma_t * normal(gen);
    }

    // Sort returns for VaR and ES calculation
    vector<double> sorted_returns = returns;
    sort(sorted_returns.begin(), sorted_returns.end());
    int var_index = static_cast<int>(N * confidence_level);
    double VaR = -sorted_returns[var_index];

    // Expected Shortfall: average of worst 1% returns
    double sum_ES = 0.0;
    for (size_t i = 0; i < static_cast<size_t>(var_index); ++i) {
        sum_ES += sorted_returns[i];
    }
    double ES = -sum_ES / var_index;

    // Calculate sample mean and standard deviation
    double mean = accumulate(returns.begin(), returns.end(), 0.0) / N;
    double sq_sum = 0.0;
    for (size_t i = 0; i < N; ++i) {
        sq_sum += pow(returns[i] - mean, 2);
    }
    double std_dev = sqrt(sq_sum / (N - 1));

    // Output results to console
    cout << "Monte Carlo Simulation of GARCH(1,1) Returns\n";
    cout << "-------------------------------------------\n";
    cout << "Simulated " << N << " returns.\n";
    cout << "Sample Mean: " << mean << "\n";
    cout << "Sample Std Dev: " << std_dev << "\n";
    cout << "1% Value at Risk (VaR): " << VaR << "\n";
    cout << "1% Expected Shortfall (ES): " << ES << "\n";

    // Save simulated returns to CSV
    ofstream outFile("simulated_returns.csv");
    outFile << "Return\n";
    for (size_t i = 0; i < returns.size(); ++i) {
        outFile << returns[i] << "\n";
    }
    outFile.close();

    
    return 0;
}
