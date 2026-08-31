#ifndef MACDINDICATOR_H
#define MACDINDICATOR_H

#include <vector>
#include <numeric>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <algorithm> 
#include "DzienAkcji.h"  
#include"Averages.h"
struct MACDResult {
    std::vector<double> macdLine;   // Linia MACD (FastEMA - SlowEMA)
    std::vector<double> signalLine; // Linia Sygnału (EMA z Linii MACD)
    std::vector<double> histogram;  // Histogram MACD (MACD Line - Signal Line)
};
class MACD {

public:
    MACD() = default;

    MACDResult calculate(const std::vector<DzienAkcji>& data,int fastPeriod = 12,int slowPeriod = 26,int signalPeriod = 9) {
        if (fastPeriod <= 0 || slowPeriod <= 0 || signalPeriod <= 0) {
            throw std::invalid_argument("Okresy dla MACD muszą być dodatnie.");
        }
        if (fastPeriod >= slowPeriod) {
            throw std::invalid_argument("Okres szybkiej EMA musi być mniejszy niż okres wolnej EMA.");
        }

        MACDResult result; // Inicjalizuj wektory od razu
        result.macdLine.assign(data.size(), std::numeric_limits<double>::quiet_NaN());
        result.signalLine.assign(data.size(), std::numeric_limits<double>::quiet_NaN());
        result.histogram.assign(data.size(), std::numeric_limits<double>::quiet_NaN());

        if (data.size() < static_cast<size_t>(slowPeriod)) {
             std::cerr << "Ostrzeżenie: Niewystarczająca ilość danych dla okresu slowPeriod: " << slowPeriod << std::endl;
            return result; // Zwróć puste/NaN wyniki
        }

        std::vector<double> closingPrices;
        closingPrices.reserve(data.size());
        for (const auto& day : data) {
            closingPrices.push_back(day.getOstatnio());
        }

        std::vector<double> fastEMA = AVERAGES::calculateEMA(closingPrices, fastPeriod);
        std::vector<double> slowEMA = AVERAGES::calculateEMA(closingPrices, slowPeriod);

        for (size_t i = 0; i < data.size(); ++i) {
            if (!std::isnan(fastEMA[i]) && !std::isnan(slowEMA[i])) {
                result.macdLine[i] = fastEMA[i] - slowEMA[i];
            }
        }

        result.signalLine = AVERAGES::calculateEMA(result.macdLine, signalPeriod);

        for (size_t i = 0; i < data.size(); ++i) {
            if (!std::isnan(result.macdLine[i]) && !std::isnan(result.signalLine[i])) {
                result.histogram[i] = result.macdLine[i] - result.signalLine[i];
            }
        }
        return result;
    }
};


#endif 
#pragma once
