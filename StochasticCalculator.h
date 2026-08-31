#ifndef STOCHASTIC_CALCULATOR_H
#define STOCHASTIC_CALCULATOR_H

#include <numeric>   // Dla std::numeric_limits
#include <cmath>     // Dla std::isnan, std::min, std::max
#include <limits>    // Dla std::numeric_limits
#include <vector>   
#include <string>    
#include <type_traits>
#include "DzienAkcji.h"     
struct StochasticResult {
    std::vector<double> k_values; // Wartości %K
    std::vector<double> d_values; // Wartości %D (SMA z %K)
};

template <typename T>
class STOCH {
public:
    STOCH() = default;

    StochasticResult calculate(const std::vector<T>& values, int kPeriod, int dPeriod) {
        if (kPeriod <= 0 || dPeriod <= 0) {
            throw std::invalid_argument("Okresy kPeriod i dPeriod muszą być dodatnie.");
        }
        StochasticResult result;
        result.k_values.assign(values.size(), std::numeric_limits<double>::quiet_NaN());
        result.d_values.assign(values.size(), std::numeric_limits<double>::quiet_NaN());

        
        size_t firstValidWindowStartIdx = 0; // Początek pierwszego okna, które ma wystarczająco danych
        if constexpr (std::is_same_v<T, double>) {
            // Znajdź pierwszy indeks, od którego values[j] przestaje być NaN
            size_t actualFirstValueIdx = 0;
            while (actualFirstValueIdx < values.size() && std::isnan(values[actualFirstValueIdx])) {
                actualFirstValueIdx++;
            }
            firstValidWindowStartIdx = actualFirstValueIdx;
        }
        // Dla DzienAkcji, firstValidWindowStartIdx pozostaje 0

      
        if (values.size() - firstValidWindowStartIdx < static_cast<size_t>(kPeriod)) {
            return result;
        }
        // --- Obliczanie %K ---
        for (size_t i = firstValidWindowStartIdx + kPeriod - 1; i < values.size(); ++i) {
            double lowestInWindow;
            double highestInWindow;
            double currentValue;
            bool windowContainsInvalidData = false;

            if constexpr (std::is_same_v<T, DzienAkcji>) {
                // Dla DzienAkcji, pobieramy min/max/ostatnio z obiektów
                lowestInWindow = values[i - kPeriod + 1].getMin();
                highestInWindow = values[i - kPeriod + 1].getMax();
                for (int j = i - kPeriod + 2; j <= static_cast<int>(i); ++j) {
                    lowestInWindow = std::min(lowestInWindow, values[j].getMin());
                    highestInWindow = std::max(highestInWindow, values[j].getMax());
                }
                currentValue = values[i].getOstatnio();
            }
            else if constexpr (std::is_same_v<T, double>) {
                if (std::isnan(values[i])) {
                    result.k_values[i] = std::numeric_limits<double>::quiet_NaN();
                    continue; 
                }

                lowestInWindow = values[i - kPeriod + 1];
                highestInWindow = values[i - kPeriod + 1];

                // Przejdź przez całe okno, aby znaleźć min/max i sprawdzić NaNy
                for (int j = i - kPeriod + 1; j <= static_cast<int>(i); ++j) {
                    if (std::isnan(values[j])) {
                        windowContainsInvalidData = true;
                        break; // Jeśli w oknie jest NaN, nie możemy obliczyć %K
                    }
                    lowestInWindow = std::min(lowestInWindow, values[j]);
                    highestInWindow = std::max(highestInWindow, values[j]);
                }
                currentValue = values[i];
            }
            else {
                throw std::runtime_error("Nieobsługiwany typ danych dla Stochastic Oscillator. Użyj DzienAkcji lub double.");
            }

            // Jeśli okno zawierało niepoprawne dane (NaN w przypadku double), pomiń obliczenia
            if (windowContainsInvalidData) {
                result.k_values[i] = std::numeric_limits<double>::quiet_NaN();
                continue;
            }

            // Obliczenie %K 
            double rangeDiff = highestInWindow - lowestInWindow;
            if (rangeDiff == 0) {
                result.k_values[i] = 100.0;
            }
            else {
                result.k_values[i] = 100.0 * (currentValue - lowestInWindow) / rangeDiff;
                // Ogranicz wynik do przedziału [0, 100]
                result.k_values[i] = std::max(0.0, std::min(100.0, result.k_values[i]));
            }
        }

        // --- Obliczanie %D (SMA z %K)
        result.d_values = AVERAGES::calculateSMA(result.k_values, dPeriod);

        return result;
    }
};

#endif