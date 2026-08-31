#ifndef AVERAGES_H
#define AVERAGES_H

#include <vector>
#include <cmath>    
#include <limits>    
#include <stdexcept> 

namespace AVERAGES {

    // Funkcja obliczająca prostą średnią kroczącą (SMA)
    inline std::vector<double> calculateSMA(const std::vector<double>& series, int period) {
        if (period <= 0) {
            throw std::invalid_argument("Okres SMA musi być dodatni.");
        }
        std::vector<double> smaValues(series.size(), std::numeric_limits<double>::quiet_NaN());
        if (series.empty() || static_cast<int>(series.size()) < period) {
            return smaValues; // Nie da się obliczyć SMA
        }

        double currentSum = 0.0;
        size_t firstValidSmaIndex = series.size();

        for (size_t i = 0; i <= series.size() - period; ++i) {
            bool windowOk = true;
            currentSum = 0.0;
            for (int k = 0; k < period; ++k) {
                if (std::isnan(series[i + k])) {
                    windowOk = false;
                    break;
                }
                currentSum += series[i + k];
            }
            if (windowOk) {
                firstValidSmaIndex = i + period - 1;
                smaValues[firstValidSmaIndex] = currentSum / period;
                break;
            }
        }

        if (firstValidSmaIndex == series.size()) {
            return smaValues;
        }

        for (size_t i = firstValidSmaIndex + 1; i < series.size(); ++i) {
            double prevElement = series[i - period];
            double currElement = series[i];

            if (!std::isnan(prevElement) && !std::isnan(currElement) && !std::isnan(smaValues[i - 1])) {
                currentSum = currentSum - prevElement + currElement;
                smaValues[i] = currentSum / period;
            }
            else {
                currentSum = 0.0;
                bool windowOk = true;
                for (int j = 0; j < period; ++j) {
                    if ((i < j) || std::isnan(series[i - j])) {
                        windowOk = false;
                        break;
                    }
                    currentSum += series[i - j];
                }
                if (windowOk) {
                    smaValues[i] = currentSum / period;
                }
                else {
                    smaValues[i] = std::numeric_limits<double>::quiet_NaN();
                }
            }
        }
        return smaValues;
    }


    // Funkcja obliczająca wykładniczą średnią kroczącą (EMA)
    // series: Wektor danych wejściowych
    // period: Okres EMA (N w wzorze k = 2/(N+1))
    inline std::vector<double> calculateEMA(const std::vector<double>& series, int period) {
        if (period <= 0) {
            throw std::invalid_argument("Okres EMA musi być dodatni.");
        }
        std::vector<double> emaValues(series.size(), std::numeric_limits<double>::quiet_NaN());
        if (series.empty() || static_cast<int>(series.size()) < period) {
            return emaValues;
        }

        // Krok 1: Oblicz początkową SMA i zainicjuj emaValues
        // Wykorzystujemy calculateSMA do uzyskania pierwszej wartości i obsługi NaN
        std::vector<double> tempSmaValues = calculateSMA(series, period);

        // Znajdź indeks pierwszej poprawnej wartości SMA
        size_t firstValidIndex = 0;
        bool foundFirstValid = false;
        for (size_t i = 0; i < tempSmaValues.size(); ++i) {
            if (!std::isnan(tempSmaValues[i])) {
                emaValues[i] = tempSmaValues[i]; // Pierwsza EMA to pierwsza SMA
                firstValidIndex = i;
                foundFirstValid = true;
                break;
            }
        }

        if (!foundFirstValid) {
            return emaValues; // Jeśli calculateSMA zwróciło same NaN
        }

        // Krok 2: Oblicz kolejne wartości EMA rekurencyjnie
        double k = 2.0 / (static_cast<double>(period) + 1.0);

        for (size_t i = firstValidIndex + 1; i < series.size(); ++i) {
            if (std::isnan(series[i])) { // Jeśli bieżąca cena/wartość jest NaN
                emaValues[i] = std::numeric_limits<double>::quiet_NaN(); // Propaguj NaN
            }
            else if (std::isnan(emaValues[i - 1])) { 
                emaValues[i] = std::numeric_limits<double>::quiet_NaN();
            }
            else {
                emaValues[i] = (series[i] * k) + (emaValues[i - 1] * (1.0 - k));
            }
        }
        return emaValues;
    }

} 
#endif
