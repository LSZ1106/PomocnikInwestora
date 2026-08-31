#ifndef STRATEGYPERFORMANCEREPORT_H
#define STRATEGYPERFORMANCEREPORT_H

#include <string>
#include <vector>
#include <iomanip> 
#include <iostream> 


struct PerformanceReport {
    std::string indicatorName;

    double initialCapital = 1.0; 
    double finalCapital = 1.0;
    double totalProfitPoints = 0.0;
    double percentageGain = 0.0;

    int totalTrades = 0;
    int winningTrades = 0;


    void calculateMetrics() {
        finalCapital = initialCapital + totalProfitPoints;
        // Oblicz zysk procentowy, jeśli kapitał początkowy był zdefiniowany (różny od zera)
        if (initialCapital != 0.0) {
            percentageGain = (totalProfitPoints / initialCapital) * 100.0;
        }
        else {
            // Jeśli kapitał początkowy był 0, zysk procentowy jest nieokreślony lub 0
            percentageGain = 0.0; 
        }
    }
};

#endif 