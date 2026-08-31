#ifndef RSIINDICATOR_H
#define RSIINDICATOR_H

#include "DzienAkcji.h"     
#include "averages.h"   
#include <vector>
#include <cmath>           
#include <limits>         
#include <stdexcept>     

class RSI {
public:
    RSI() = default;

    std::vector<double> calculate(const std::vector<DzienAkcji>& data, int n_period = 14) {
        if (n_period <= 0) {
            throw std::invalid_argument("Okres RSI musi być dodatni.");
        }
        if (data.size() < static_cast<size_t>(n_period + 1)) {
            // Za mało danych na RSI — zwracamy same NaN.
            return std::vector<double>(data.size(), std::numeric_limits<double>::quiet_NaN());
        }

        const size_t dataSize = data.size();
        std::vector<double> gains(dataSize, 0.0);
        std::vector<double> losses(dataSize, 0.0);

        // Obliczamy dzienne zmiany (zyski i straty).
        for (size_t i = 1; i < dataSize; ++i) {
            double prevClose = data[i - 1].getOstatnio();
            double currClose = data[i].getOstatnio();

            if (std::isnan(prevClose) || std::isnan(currClose)) {
                gains[i] = std::numeric_limits<double>::quiet_NaN();
                losses[i] = std::numeric_limits<double>::quiet_NaN();
                continue;
            }

            double change = currClose - prevClose;
            if (change > 0) {
                gains[i] = change;
                losses[i] = 0.0;
            }
            else {
                gains[i] = 0.0;
                losses[i] = std::abs(change);
            }
        }

        // Używamy okresu wygładzenia ema_period = (2 * n_period) - 1
        int ema_period = (2 * n_period) - 1;

        std::vector<double> avgGains = AVERAGES::calculateEMA(gains, ema_period);
        std::vector<double> avgLosses = AVERAGES::calculateEMA(losses, ema_period);

        std::vector<double> rsiValues(dataSize, std::numeric_limits<double>::quiet_NaN());

        // Obliczamy RSI
        for (size_t i = 0; i < dataSize; ++i) {
            double ag = avgGains[i];
            double al = avgLosses[i];

            if (std::isnan(ag) || std::isnan(al)) {
                // Brak danych lub NaN wcześniej – zostawiamy NaN
                continue;
            }

            if (al == 0.0 && ag == 0.0) {
                rsiValues[i] = 50.0; // brak trendu
            }
            else if (al == 0.0) {
                rsiValues[i] = 100.0; // tylko wzrosty
            }
            else if (ag == 0.0) {
                rsiValues[i] = 0.0;   // tylko spadki
            }
            else {
                double rs = ag / al;
                rsiValues[i] = 100.0 - (100.0 / (1.0 + rs));
            }
        }

        return rsiValues;
    }
};

#endif 
