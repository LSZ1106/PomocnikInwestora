#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

#include "CzytnikCSV.h"
#include "DzienAkcji.h"

#include "MovingAverageIndicator.h"
#include "RSI.h"
#include "StochasticCalculator.h"
#include "MACDIndicator.h"
#include "signal_generators.h" 
#include "PerformanceReport.h"
#include "Simulate.h" 
#include "averages.h"


struct Settings {
    std::string csvFilePath;
    int rsiPeriod = 14;
    double rsiOversold = 30.0;
    double rsiOverbought = 70.0;
    int maPeriod1 = 5;
    int maPeriod2 = 10;
    int stochKPeriod = 9;
    int stochDPeriod = 6;
    int macdFastPeriod = 12;
    int macdSlowPeriod = 26;
    int macdSignalPeriod = 9;
    int stochRsiRsiPeriod = 14;
    int StochRsiKPeriod = 14;
    int stochRsiDPeriod = 3;
    double initialCapital = 10000.0;
    int simulationDays;
};


class AppLogic {
public:
    std::vector<PerformanceReport> runSimulation(const Settings& settings, std::string& consoleOutput) {
        std::stringstream ss;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::streambuf* oldCerr = std::cerr.rdbuf();
        std::cout.rdbuf(ss.rdbuf());
        std::cerr.rdbuf(ss.rdbuf());

        std::vector<PerformanceReport> allReports;

        CzytnikCSV czytnik;
        MovingAverage maCalculator;
        RSI rsiCalculator;
        STOCH <DzienAkcji>stochCalculator;
        MACD macdCalculator;
        STOCH<double> stochRsiCalculator;

        std::vector<DzienAkcji> allRawData;

        try {
            allRawData = czytnik.wczytajDane(settings.csvFilePath, true);
            std::cout << "Wczytano " << allRawData.size() << " rekordow z pliku: " << settings.csvFilePath << ".\n";

            if (!allRawData.empty() && allRawData[0].getData() > allRawData.back().getData()) {
                std::reverse(allRawData.begin(), allRawData.end());
                // std::cout << "Info: Odwrocono dane do chronologicznej kolejnosci.\n";
            }

            const int MIN_REKORDOW_GLOBAL = 100;
            if (allRawData.size() < MIN_REKORDOW_GLOBAL) {
                std::cerr << "Blad: Za malo danych (" << allRawData.size()
                    << ") w pliku dla startu obliczen. Trzeba min. " << MIN_REKORDOW_GLOBAL << ".\n";
                consoleOutput = ss.str();
                std::cout.rdbuf(oldCout);
                std::cerr.rdbuf(oldCerr);
                return allReports;
            }

            const int MAX_LOOKBACK_PERIOD = 70;

            int actualSimulationDays = settings.simulationDays;
            if (actualSimulationDays > static_cast<int>(allRawData.size()) - MAX_LOOKBACK_PERIOD) {
                actualSimulationDays = static_cast<int>(allRawData.size()) - MAX_LOOKBACK_PERIOD;
                if (actualSimulationDays < 1) {
                    std::cout.rdbuf(oldCout);
                    std::cerr.rdbuf(oldCerr);

                    throw std::runtime_error("Za malo danych w pliku dla liczby dni symulacji");
                }

                std::cout << "Ostrzezenie: Liczba dni symulacji zmniejszona do " << actualSimulationDays
                    << " z uwagi na dane\n";
            }

            DzienAkcji::Date simulationEndDate = allRawData.back().getData();
            DzienAkcji::Date simulationStartDate = simulationEndDate.addDays(-(actualSimulationDays - 1));
            DzienAkcji::Date indicatorCalculationStartDate = simulationStartDate.addDays(-MAX_LOOKBACK_PERIOD);

            std::vector<DzienAkcji> dataForIndicators;
            for (const auto& d : allRawData) {
                if (d.getData() >= indicatorCalculationStartDate && d.getData() <= simulationEndDate) {
                    dataForIndicators.push_back(d);
                }
                else if (d.getData() > simulationEndDate) {
                    break;
                }
            }

            const int MIN_REKORDOW_DLA_WSKAZNIKOW = MAX_LOOKBACK_PERIOD;
            if (dataForIndicators.size() < MIN_REKORDOW_DLA_WSKAZNIKOW) {
                std::cerr << "Blad: Za malo danych (" << dataForIndicators.size()
                    << ") w zakresie obliczen wskaznikow (trzeba min. " << MIN_REKORDOW_DLA_WSKAZNIKOW << ").\n";
                consoleOutput = ss.str();
                std::cout.rdbuf(oldCout);
                std::cerr.rdbuf(oldCerr);
                return allReports;
            }


            /* std::cout << "Obliczenia wskaznikow od: " << indicatorCalculationStartDate.toString()
                 << " do: " << simulationEndDate.toString()
                 << " (" << dataForIndicators.size() << " rekordow).\n";
                 */
            std::map<std::string, std::vector<double>> allIndicatorSeries;

            allIndicatorSeries["MA_5"] = maCalculator.calculate(dataForIndicators, settings.maPeriod1);
            allIndicatorSeries["MA_10"] = maCalculator.calculate(dataForIndicators, settings.maPeriod2);

            allIndicatorSeries["RSI_" + std::to_string(settings.rsiPeriod)] = rsiCalculator.calculate(dataForIndicators, settings.rsiPeriod);
            if (settings.rsiPeriod != settings.stochRsiRsiPeriod) {
                allIndicatorSeries["RSI_" + std::to_string(settings.stochRsiRsiPeriod)] = rsiCalculator.calculate(dataForIndicators, settings.stochRsiRsiPeriod);
            }
            StochasticResult stochWyniki_temp = stochCalculator.calculate(dataForIndicators, settings.stochKPeriod, settings.stochDPeriod);
            allIndicatorSeries["STOCH_K_" + std::to_string(settings.stochKPeriod) + "_" + std::to_string(settings.stochDPeriod)] = stochWyniki_temp.k_values;
            allIndicatorSeries["STOCH_D_" + std::to_string(settings.stochKPeriod) + "_" + std::to_string(settings.stochDPeriod)] = stochWyniki_temp.d_values;

            MACDResult macdWyniki_temp = macdCalculator.calculate(dataForIndicators, settings.macdFastPeriod, settings.macdSlowPeriod, settings.macdSignalPeriod);
            allIndicatorSeries["MACD_Line_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod)] = macdWyniki_temp.macdLine;
            allIndicatorSeries["MACD_Signal_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod)] = macdWyniki_temp.signalLine;
            allIndicatorSeries["MACD_Hist_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod)] = macdWyniki_temp.histogram;

            const std::string rsiKeyForStochRsi = "RSI_" + std::to_string(settings.stochRsiRsiPeriod);
            if (allIndicatorSeries.count(rsiKeyForStochRsi)) {
                StochasticResult stochRsiWyniki_temp = stochRsiCalculator.calculate(allIndicatorSeries.at(rsiKeyForStochRsi), settings.StochRsiKPeriod, settings.stochRsiDPeriod);
                allIndicatorSeries["STOCHRSI_K_" + std::to_string(settings.stochRsiRsiPeriod) + "_" + std::to_string(settings.StochRsiKPeriod) + "_" + std::to_string(settings.stochRsiDPeriod)] = stochRsiWyniki_temp.k_values;
                allIndicatorSeries["STOCHRSI_D_" + std::to_string(settings.stochRsiRsiPeriod) + "_" + std::to_string(settings.StochRsiKPeriod) + "_" + std::to_string(settings.stochRsiDPeriod)] = stochRsiWyniki_temp.d_values;
            }
            else {

                std::cerr << "Ostrzezenie: RSI dla StochRSI (" << rsiKeyForStochRsi << ") nie znaleziono. StochRSI nie bedzie liczone.\n";
            }

            // std::cout << "Obliczenia wskaznikow zakonczone.\n";

            std::vector<DzienAkcji> simulationData;
            //  Przygotowanie danych do symulacji
           // Określenie indeksu początkowego w danych wskaźników, od którego ma rozpocząć się symulacja.
           // Pętla szuka pierwszego rekordu, który jest zgodny z datą rozpoczęcia symulacji.

            size_t startIndexInIndicatorData = 0;

            bool foundSimStartDate = false;
            for (size_t i = 0; i < dataForIndicators.size(); ++i) {
                if (dataForIndicators[i].getData() >= simulationStartDate) {
                    startIndexInIndicatorData = i;
                    foundSimStartDate = true;
                    break;
                }
            }

            if (!foundSimStartDate) {
                std::cout.rdbuf(oldCout);
                std::cerr.rdbuf(oldCerr);

                throw std::runtime_error("Brak danych dla okresu symulacji");
            }
            // Filtracja danych historycznych, aby stworzyć `simulationData`,
            // która zawiera tylko dni w faktycznym okresie symulacji.
            // Pętla iteruje od znalezionego `startIndexInIndicatorData` do końca zakresu symulacji.

            for (size_t i = startIndexInIndicatorData; i < dataForIndicators.size(); ++i) {
                if (dataForIndicators[i].getData() <= simulationEndDate) {
                    simulationData.push_back(dataForIndicators[i]);
                }
                else {
                    break;
                }
            }

            if (simulationData.empty()) {
                std::cout.rdbuf(oldCout);
                std::cerr.rdbuf(oldCerr);

                throw std::runtime_error("Brak danych w okresie symulacji.");
            }
            // Filtracja obliczonych serii wskaźników, aby odpowiadały zakresowi `simulationData`.
            // Pętla przechodzi przez wszystkie obliczone serie wskaźników w `allIndicatorSeries`
            // i tworzy odpowiednio skrócone serie w `simulationIndicatorSeries`.

            std::map<std::string, std::vector<double>> simulationIndicatorSeries;
            for (auto const& pair : allIndicatorSeries) {
                const std::string& key = pair.first;
                const std::vector<double>& val = pair.second;
                if (val.size() > startIndexInIndicatorData) {
                    std::vector<double> filteredSeries;
                    for (size_t i = startIndexInIndicatorData; i < val.size(); ++i) {
                        if (i - startIndexInIndicatorData < simulationData.size()) {
                            filteredSeries.push_back(val[i]);
                        }
                        else {
                            break;
                        }
                    }
                    simulationIndicatorSeries[key] = filteredSeries;
                }
                else {

                    std::cerr << "Ostrzezenie: Wskaznik " << key << " mial za malo danych.\n";
                }
            }


            std::cout << "Okres symulacji: " << simulationStartDate.toString() << " - "
                << simulationEndDate.toString() << " (" << simulationData.size() << " dni handlowych).\n\n";



            // 1. Symulacja dla MA Crossover (przecięcie dwóch średnich ruchomych)
            allReports.push_back(simulate(
                "MA Crossover (" + std::to_string(settings.maPeriod1) + " vs " + std::to_string(settings.maPeriod2) + ")",
                simulationData, simulationIndicatorSeries,
                // Lambda funkcja definiująca, jak generować sygnały dla tej strategii.
                // Na podstawie bieżących i poprzednich wartości MA generowany jest sygnał kupna/sprzedaży.
                [&](size_t idx, const std::vector<DzienAkcji>& pData, const std::map<std::string, std::vector<double>>& indS) -> SignalType {
                    const std::string maShortKey = "MA_5";
                    const std::string maLongKey = "MA_10";
                    // Sprawdzenie, czy dane są dostępne i czy indeks jest prawidłowy
                    if (idx == 0 || !indS.count(maShortKey) || !indS.count(maLongKey) ||
                        idx >= indS.at(maShortKey).size() || idx >= indS.at(maLongKey).size()) {
                        return SignalType::NONE; // Brak sygnału, jeśli dane są niewystarczające
                    }
                    // Wywołanie funkcji z generatorów sygnałów do określenia akcji handlowej
                    return TradingSignals::getMACrossoverAction(
                        indS.at(maShortKey)[idx], indS.at(maLongKey)[idx],
                        indS.at(maShortKey)[idx - 1], indS.at(maLongKey)[idx - 1],
                        pData[idx].getOstatnio(), pData[idx - 1].getOstatnio()
                    );
                },
                settings.initialCapital));

            // 2. Symulacja dla RSI Wilder (Relative Strength Index)
            allReports.push_back(simulate(
                "RSI (" + std::to_string(settings.rsiPeriod) + ", " + std::to_string(static_cast<int>(settings.rsiOversold)) + "/" + std::to_string(static_cast<int>(settings.rsiOverbought)) + ")",
                simulationData, simulationIndicatorSeries,
                // Lambda funkcja dla logiki sygnałów RSI
                [&](size_t idx, const std::vector<DzienAkcji>& pData, const std::map<std::string, std::vector<double>>& indS) -> SignalType {
                    const std::string rsiKey = "RSI_" + std::to_string(settings.rsiPeriod);
                    if (idx == 0 || !indS.count(rsiKey) || idx >= indS.at(rsiKey).size()) {
                        return SignalType::NONE;
                    }
                    return TradingSignals::getRSIAction(
                        indS.at(rsiKey)[idx],
                        indS.at(rsiKey)[idx - 1],
                        settings.rsiOversold, settings.rsiOverbought,
                        pData[idx].getOstatnio(), pData[idx - 1].getOstatnio()
                    );
                },
                settings.initialCapital));

            // 3. Symulacja dla Stochastic Oscillator
            const std::string stochKKey = "STOCH_K_" + std::to_string(settings.stochKPeriod) + "_" + std::to_string(settings.stochDPeriod);
            const std::string stochDKey = "STOCH_D_" + std::to_string(settings.stochKPeriod) + "_" + std::to_string(settings.stochDPeriod);
            if (simulationIndicatorSeries.count(stochKKey) && simulationIndicatorSeries.count(stochDKey)) {
                allReports.push_back(simulate(
                    "Stochastic (" + std::to_string(settings.stochKPeriod) + "," + std::to_string(settings.stochDPeriod) + ", 20/80)",
                    simulationData, simulationIndicatorSeries,
                    // Lambda funkcja dla logiki sygnałów Stochastic
                    [&](size_t idx, const std::vector<DzienAkcji>& pData, const std::map<std::string, std::vector<double>>& indS) -> SignalType {
                        if (idx == 0 || !indS.count(stochKKey) || !indS.count(stochDKey) ||
                            idx >= indS.at(stochKKey).size() || idx >= indS.at(stochDKey).size()) {
                            return SignalType::NONE;
                        }
                        return TradingSignals::getStochasticAction(
                            indS.at(stochKKey)[idx], indS.at(stochDKey)[idx],
                            indS.at(stochKKey)[idx - 1], indS.at(stochDKey)[idx - 1]);
                    },
                    settings.initialCapital));
            }
            else {
                std::cerr << "Ostrzezenie: Stochastic K/D nie znaleziono w danych, nie bedzie liczone Stochastic.\n";
            }

            // 4. Symulacja dla MACD (Moving Average Convergence Divergence)
            const std::string macdLineKey = "MACD_Line_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod);
            const std::string macdSignalKey = "MACD_Signal_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod);
            const std::string macdHistKey = "MACD_Hist_" + std::to_string(settings.macdFastPeriod) + "_" + std::to_string(settings.macdSlowPeriod) + "_" + std::to_string(settings.macdSignalPeriod);

            if (simulationIndicatorSeries.count(macdLineKey) && simulationIndicatorSeries.count(macdSignalKey) && simulationIndicatorSeries.count(macdHistKey)) {
                allReports.push_back(simulate(
                    "MACD (" + std::to_string(settings.macdFastPeriod) + "," + std::to_string(settings.macdSlowPeriod) + "," + std::to_string(settings.macdSignalPeriod) + ")",
                    simulationData, simulationIndicatorSeries,
                    // Lambda funkcja dla logiki sygnałów MACD
                    [&](size_t idx, const std::vector<DzienAkcji>& pData, const std::map<std::string, std::vector<double>>& indS) -> SignalType {
                        if (idx == 0 || !indS.count(macdLineKey) || !indS.count(macdSignalKey) || !indS.count(macdHistKey) ||
                            idx >= indS.at(macdLineKey).size() || idx >= indS.at(macdSignalKey).size() || idx >= indS.at(macdHistKey).size()) {
                            return SignalType::NONE;
                        }
                        return TradingSignals::getMACDAction(
                            indS.at(macdLineKey)[idx], indS.at(macdSignalKey)[idx], indS.at(macdHistKey)[idx],
                            indS.at(macdLineKey)[idx - 1], indS.at(macdSignalKey)[idx - 1], indS.at(macdHistKey)[idx - 1]);
                    },
                    settings.initialCapital));
            }
            else {
                std::cerr << "Ostrzezenie: MACD linie nie znaleziono w danych, nie bedzie liczone MACD.\n";
            }

            // 5. Symulacja dla StochRSI (Stochastic Relative Strength Index)
            const std::string stochRsiKKey = "STOCHRSI_K_" + std::to_string(settings.stochRsiRsiPeriod) + "_" + std::to_string(settings.StochRsiKPeriod) + "_" + std::to_string(settings.stochRsiDPeriod);
            const std::string stochRsiDKey = "STOCHRSI_D_" + std::to_string(settings.stochRsiRsiPeriod) + "_" + std::to_string(settings.StochRsiKPeriod) + "_" + std::to_string(settings.stochRsiDPeriod);
            if (simulationIndicatorSeries.count(stochRsiKKey) && simulationIndicatorSeries.count(stochRsiDKey)) {
                allReports.push_back(simulate(
                    "StochRSI ("+ std::to_string(settings.stochRsiRsiPeriod) + "," + std::to_string(settings.StochRsiKPeriod) + "," + std::to_string(settings.stochRsiDPeriod) + ", 20/80)", // Przykład nazwy, można dostosować do dynamicznych parametrów
                    simulationData, simulationIndicatorSeries,
                    // Lambda funkcja dla logiki sygnałów StochRSI
                    [&](size_t idx, const std::vector<DzienAkcji>& pData, const std::map<std::string, std::vector<double>>& indS) -> SignalType {
                        if (idx == 0 || !indS.count(stochRsiKKey) || !indS.count(stochRsiDKey) ||
                            idx >= indS.at(stochRsiKKey).size() || idx >= indS.at(stochRsiDKey).size()) {
                            return SignalType::NONE;
                        }
                        return TradingSignals::getStochRSIAction(
                            indS.at(stochRsiKKey)[idx], indS.at(stochRsiDKey)[idx],
                            indS.at(stochRsiKKey)[idx - 1], indS.at(stochRsiDKey)[idx - 1]);
                    },
                    settings.initialCapital));
            }
            else {
                std::cerr << "Ostrzezenie: StochRSI K/D nie znaleziono w danych, nie bedzie liczone StochRSI.\n";
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "\n*** Blad: " << e.what() << " ***" << std::endl;
        }
        catch (const std::exception& e) {

            std::cerr << "\n*** Krytyczny blad: " << e.what() << " ***" << std::endl;
        }
        catch (...) {

            std::cerr << "\n*** Nieznany krytyczny blad! ***" << std::endl;
        }

        consoleOutput = ss.str();
        std::cout.rdbuf(oldCout);
        std::cerr.rdbuf(oldCerr);
        return allReports;
    }
};