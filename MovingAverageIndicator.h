#ifndef MOVINGAVERAGEINDICATOR_H
#define MOVINGAVERAGEINDICATOR_H

#include "DzienAkcji.h"        
#include "RSI.h" 

class MovingAverage {
public:
    MovingAverage() = default;

    std::vector<double> calculate(const std::vector<DzienAkcji>& data, int period) {
        if (period <= 0) {
            throw std::invalid_argument("Okres dla MA musi być dodatni.");
        }

        std::vector<double> closingPrices;
        closingPrices.reserve(data.size());
        for (const auto& day : data) {
            closingPrices.push_back(day.getOstatnio()); 
        }
        return AVERAGES::calculateSMA(closingPrices, period);
    }

    // Przeciążona wersja przyjmująca bezpośrednio wektor cen
    std::vector<double> calculate(const std::vector<double>& prices, int period) {
        if (period <= 0) {
            throw std::invalid_argument("Okres dla MA musi być dodatni.");
        }
        return AVERAGES::calculateSMA(prices, period);
    }
};

#endif
