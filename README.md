# Crypto Time Series Analysis

This repository contains my QFE5340 Financial Econometrics Project (April 28, 2025), focused on modeling dependence, predictability, and time-varying correlation in cryptocurrency returns using **VAR(1)** and **DCC-GARCH(1,1)**.

The analysis uses five major cryptocurrencies: **BTC, ETH, BNB, XRP, and DOGE**.

---

## Motivation

Cryptocurrency markets are highly volatile and often move together during market stress.  
The goal of this project is to understand:

- how strongly major crypto returns co-move (correlation structure),
- whether any crypto return series helps predict others (Granger causality in a VAR framework),
- how shocks propagate across assets (IRF),
- whether forecast uncertainty is driven mostly by own shocks or cross shocks (FEVD),
- and how correlations evolve through time (DCC-GARCH).

---

## Data

The script expects a **long-format** CSV at:

- `data/crypto.csv`

Required columns:

- `timestamp` (date-time)
- `symbol` (BTC, ETH, BNB, XRP, DOGE)
- `return` (return at your sampling frequency)

> The `data/` folder is tracked, but **CSV files are ignored** by `.gitignore` to avoid uploading raw datasets to GitHub.

---

## Methods

### 1) Descriptive statistics
Using 99,511 observations in the project dataset, mean returns are near zero (consistent with market efficiency).  
Volatility is higher for **XRP and DOGE** relative to BTC/ETH/BNB.

### 2) Correlation + heatmap
All five cryptocurrencies are positively correlated, with **BTC–ETH** showing one of the strongest relationships (≈ 0.77 in the project report).

### 3) VAR(1) + Granger causality
A VAR(1) model is estimated (trimmed sample used due to computation limits).  
Granger causality tests are used to evaluate predictive relationships across the system. In the report results, **BTC, ETH, BNB, and DOGE** show predictive power for the system, while **XRP appears relatively more independent** (fails to Granger-cause others at 5%).

### 4) IRF + FEVD
- **IRF:** shocks to BTC have a short-run positive effect on ETH that fades quickly.
- **FEVD:** most forecast uncertainty is dominated by each asset’s own shocks; cross-asset contributions are smaller.

### 5) DCC-GARCH(1,1)
Dynamic conditional correlations are highly persistent.  
In the report results, the DCC parameters suggest:
- **α (shock effect)** is statistically significant but small,
- **β (persistence)** is very large (≈ 0.98),
- indicating correlation is strongly driven by past correlation and only modestly by new shocks.


---

## Key Findings (from the project report)

- Mean returns are close to zero, while volatility differs across assets (XRP/DOGE more volatile).
- BTC, ETH, and BNB exhibit stronger co-movement than XRP.
- Granger causality results support BTC’s dominant role in predictive relationships.
- Shock spillovers appear short-lived in impulse responses.
- DCC-GARCH confirms crypto correlations are time-varying and highly persistent.

---

## How to run

Install packages (first time only):

```r
install.packages(c("data.table","vars","ggplot2","reshape2","igraph","rmgarch"))
