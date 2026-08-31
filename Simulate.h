#include "signal_generators.h"
#include "DzienAkcji.h" 
#include <cmath>
#include "PerformanceReport.h" 
#include <iostream> 
#include <limits> 

using SignalGeneratorFunc = std::function<SignalType(
    size_t currentIndex,
    const std::vector<DzienAkcji>& allPriceData, 
    const std::map<std::string, std::vector<double>>& allIndicatorSeries 
)>;

PerformanceReport simulate(
    const std::string& indicatorDescription,
    const std::vector<DzienAkcji>& priceData,
    const std::map<std::string, std::vector<double>>& indicatorSeries,
    SignalGeneratorFunc signalFunction,
    double initialCapitalForPercentageCalc = 0.0 
) {
    PerformanceReport report;
    report.indicatorName = indicatorDescription;
    report.initialCapital = initialCapitalForPercentageCalc;

    bool inMarket = false;      
    double entryPrice = 0.0;
    double accumulatedProfitPoints = 0.0;

    if (priceData.empty()) {
        report.calculateMetrics();
        return report;
    }

    // Określ minimalny indeks początkowy dla danych, aby uniknąć NaNów
    // Musi być co najmniej 1, aby mieć priceData[i-1]
    // Ale także musi uwzględniać opóźnienie wskaźników (najdłuższy okres)
    size_t min_start_idx = 1; // Minimalny start, aby mieć dostęp do [i-1]

    // Znajdź najdłuższy okres wskaźnika, aby zacząć symulację od sensownych danych
    for (const auto& pair : indicatorSeries) {
        // Zakładamy, że NaN są na początku, więc szukamy pierwszego nie-NaN
        for (size_t k = 0; k < pair.second.size(); ++k) {
            // Sprawdzamy czy wartość jest NaN (może być wynikiem niemożności obliczenia dla początkowych dni)
            if (!std::isnan(pair.second[k]) && pair.second[k] != -1.0) { 
                if (k + 1 > min_start_idx) {
                    min_start_idx = k + 1;
                }
                break; // Znaleziono pierwszą ważną wartość dla tego wskaźnika, idź do następnego wskaźnika
            }
        }
    }

    if (min_start_idx >= priceData.size()) {
        std::cerr << "Błąd: Niewystarczająca ilość danych dla symulacji " << indicatorDescription << " po uwzględnieniu okresu rozgrzewkowego wskaźników.\n";
        report.calculateMetrics();
        return report;
    }

  
    for (size_t i = min_start_idx; i < priceData.size(); ++i) { 
        SignalType action = signalFunction(i, priceData, indicatorSeries);

        double currentPrice = priceData[i].getOstatnio();

        if (std::isnan(currentPrice)) continue; // Pomiń dzień, jeśli cena jest NaN

        SignalType signal = action;

        if (inMarket) {
            if (signal == SignalType::SELL) {
  
                double tradeProfit = currentPrice - entryPrice;
                accumulatedProfitPoints += tradeProfit;
                report.totalTrades++;
                if (tradeProfit > 0) {
                    report.winningTrades++;
                }
                // std::cout << priceData[i].getData().toString() << ": SPRZEDAJ @ " << currentPrice << ", Zysk/Strata jednostkowa: " << tradeProfit << std::endl;
                inMarket = false;
            }
        }
        else { 
            if (signal == SignalType::BUY) {
                entryPrice = currentPrice;
                inMarket = true;
                // std::cout << priceData[i].getData().toString() << ": KUP @ " << entryPrice << std::endl;
            }
        }
    }

    // Jeśli na końcu danych pozycja jest nadal otwarta, zamykamy ją po ostatniej cenie
    if (inMarket) {
        double lastPrice = priceData.back().getOstatnio();
        if (!std::isnan(lastPrice)) {
            double tradeProfit = lastPrice - entryPrice;
            accumulatedProfitPoints += tradeProfit;
            report.totalTrades++;
            if (tradeProfit > 0) {
                report.winningTrades++;
            }
            
            // std::cout << priceData.back().getData().toString() << ": ZAMKNIJ POZYCJĘ (koniec danych) @ " << lastPrice << ", Zysk/Strata jednostkowa: " << tradeProfit << std::endl;
        }
        inMarket = false;
    }

    report.totalProfitPoints = accumulatedProfitPoints;
    report.calculateMetrics(); // Oblicza finalCapital i percentageGain

    return report;
}