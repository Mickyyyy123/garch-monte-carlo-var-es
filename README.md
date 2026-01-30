# garch-monte-carlo-var-es
# GARCH(1,1) Monte Carlo Simulation — VaR & Expected Shortfall

This project simulates 1,000,000 returns using a GARCH(1,1) volatility model and estimates downside risk through Value at Risk (VaR) and Expected Shortfall (ES).

## Model
Returns are generated as:

r_t = σ_t z_t,  z_t ~ N(0,1)

σ_t² = ω + α r_{t−1}² + β σ_{t−1}²

## Risk Metrics
- 1% Value at Risk (VaR)
- 1% Expected Shortfall (ES)

## Implementation
- Language: C++
- RNG: Mersenne Twister (fixed seed for reproducibility)
- Simulation size: 1,000,000 observations

## How to Run

```bash
g++ -O2 -std=c++17 src/garchmontecarlo.cpp -o garch_sim
./garch_sim
