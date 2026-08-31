#include "pch.h"
#include "signal_generators.h" 
#include <string>
#include <cmath> 
#include <stdexcept>
std::string TradingSignals::signalTypeToString(SignalType signal) {
    switch (signal) {
    case SignalType::BUY:
        return "KUP";
    case SignalType::SELL:
        return "SPRZEDAJ";
    case SignalType::NONE:
        return "BRAK_SYGNALU";
    default:
        throw std::runtime_error("Nieznany typ sygnału!");
    }
}
SignalType TradingSignals::getMACrossoverAction(double ma_short_curr, double ma_long_curr,
    double ma_short_prev, double ma_long_prev,
    double price_curr, double price_prev) {
    if (std::isnan(ma_short_curr) || std::isnan(ma_long_curr) ||
        std::isnan(ma_short_prev) || std::isnan(ma_long_prev) ||
        std::isnan(price_curr) || std::isnan(price_prev)) {
        return SignalType::NONE;
    }

    bool is_bullish_crossover = (ma_short_prev < ma_long_prev && ma_short_curr > ma_long_curr);
    bool is_bearish_crossover = (ma_short_prev > ma_long_prev && ma_short_curr < ma_long_curr);

    bool ma_short_rising = (ma_short_curr > ma_short_prev);
    bool ma_long_rising = (ma_long_curr > ma_long_prev);
    bool ma_short_falling = (ma_short_curr < ma_short_prev);
    bool ma_long_falling = (ma_long_curr < ma_long_prev);

    // Krótka MA przecina długą MA w górę, obie MA rosną, a cena jest nad długą MA.
    if (is_bullish_crossover && ma_short_rising && ma_long_rising && price_curr > ma_long_curr) {
        return SignalType::BUY;
    }
    // Krótka MA przecina długą MA w dół, obie MA spadają, a cena jest pod długą MA.
    if (is_bearish_crossover && ma_short_falling && ma_long_falling && price_curr < ma_long_curr) {
        return SignalType::SELL;
    }
    // Krótka MA przecina długą MA w górę, a cena potwierdza to, przechodząc powyżej krótkiej MA.
    if (is_bullish_crossover && price_prev < ma_short_prev && price_curr > ma_short_curr) {
        return SignalType::BUY;
    }
    // Krótka MA przecina długą MA w dół, a cena potwierdza to, przechodząc poniżej krótkiej MA.
    if (is_bearish_crossover && price_prev > ma_short_prev && price_curr < ma_short_curr) {
        return SignalType::SELL;
    }
    return SignalType::NONE;
}

SignalType TradingSignals::getRSIAction(double rsi_curr, double rsi_prev,
    double oversold_threshold, double overbought_threshold,
    double price_curr, double price_prev) {
    if (std::isnan(rsi_curr) || std::isnan(rsi_prev) ||
        std::isnan(price_curr) || std::isnan(price_prev)) {
        return SignalType::NONE;
    }
    // Cena robi niższy dołek, a RSI wyższy dołek. Wskazuje na możliwe odwrócenie trendu spadkowego.
    // Dodatkowo: Upewniamy się, że RSI jest w strefie wyprzedania lub blisko niej dla większej wiarygodności.
    if (price_curr < price_prev && rsi_curr > rsi_prev && rsi_curr <= oversold_threshold + 5) {
        return SignalType::BUY;
    }
    // Cena robi wyższy szczyt, a RSI niższy szczyt. Wskazuje na możliwe odwrócenie trendu wzrostowego.
    // Dodatkowo: Upewniamy się, że RSI jest w strefie wykupienia lub blisko niej dla większej wiarygodności.
    if (price_curr > price_prev && rsi_curr < rsi_prev && rsi_curr >= overbought_threshold - 5) {
        return SignalType::SELL;
    }
    // RSI było w strefie wyprzedania i właśnie z niej wyszło.
    if (rsi_prev < oversold_threshold && rsi_curr >= oversold_threshold) {
        return SignalType::BUY;
    }
    // RSI było w strefie wykupienia i właśnie z niej wyszło.
    if (rsi_prev > overbought_threshold && rsi_curr <= overbought_threshold) {
        return SignalType::SELL;
    }
// Może to być sygnał kontynuacji trendu wzrostowego lub jego rozpoczęcia.
    if (rsi_prev < 50 && rsi_curr >= 50) {
        return SignalType::BUY;
    }
    // Może to być sygnał kontynuacji trendu spadkowego lub jego rozpoczęcia.
    if (rsi_prev > 50 && rsi_curr <= 50) {
        return SignalType::SELL;
    }
    return SignalType::NONE;
}
SignalType TradingSignals::getOscillatorCrossoverAction(
    double k_curr, double d_curr,
    double k_prev, double d_prev,
    double oversold_threshold, double overbought_threshold) {

    if (std::isnan(k_curr) || std::isnan(d_curr) ||
        std::isnan(k_prev) || std::isnan(d_prev)) {
        return SignalType::NONE;
    }

    bool is_bullish_crossover = (k_prev < d_prev && k_curr > d_curr);
    bool is_bearish_crossover = (k_prev > d_prev && k_curr < d_curr);
    if (is_bullish_crossover && k_prev < oversold_threshold && d_prev < oversold_threshold) {
        return SignalType::BUY;
    }
    // K przecina D w dół, gdy oba wskaźniki były w strefie wykupienia.
    if (is_bearish_crossover && k_prev > overbought_threshold && d_prev > overbought_threshold) {
        return SignalType::SELL;
    }
    // K przecina D w górę, a K właśnie wychodzi ze strefy wyprzedania.
    if (is_bullish_crossover && k_curr >= oversold_threshold && k_prev < oversold_threshold) {
        return SignalType::BUY;
    }
    // K przecina D w dół, a K właśnie wychodzi ze strefy wykupienia.
    if (is_bearish_crossover && k_curr <= overbought_threshold && k_prev > overbought_threshold) {
        return SignalType::SELL;
    }
    return SignalType::NONE;
}
SignalType TradingSignals::getStochasticAction(
    double k_curr, double d_curr,
    double k_prev, double d_prev,
    double oversold, double overbought) {
    return getOscillatorCrossoverAction(k_curr, d_curr, k_prev, d_prev, oversold, overbought);
}

SignalType TradingSignals::getStochRSIAction(
    double k_curr, double d_curr,
    double k_prev, double d_prev,
    double oversold, double overbought) {
    return getOscillatorCrossoverAction(k_curr, d_curr, k_prev, d_prev, oversold, overbought);
}
   

SignalType TradingSignals::getMACDAction(
    double macd_curr, double signal_curr, double histogram_curr,
    double macd_prev, double signal_prev, double histogram_prev
) {
    if (std::isnan(macd_curr) || std::isnan(signal_curr) || std::isnan(histogram_curr) ||
        std::isnan(macd_prev) || std::isnan(signal_prev) || std::isnan(histogram_prev)) {
        return SignalType::NONE;
    }

    bool is_bullish_crossover = (macd_prev < signal_prev && macd_curr > signal_curr);
    bool is_bearish_crossover = (macd_prev > signal_prev && macd_curr < signal_curr);

    // Histogram przechodzi z ujemnego na dodatni, a MACD i Signal Line są pod linią zerową, ale MACD rośnie.
    if (histogram_prev < 0 && histogram_curr > 0 && macd_curr < 0 && signal_curr < 0 && macd_curr > macd_prev) {
        return SignalType::BUY;
    }
    // Histogram przechodzi z dodatniego na ujemny, a MACD i Signal Line są nad linią zerową, ale MACD spada.
    if (histogram_prev > 0 && histogram_curr < 0 && macd_curr > 0 && signal_curr > 0 && macd_curr < macd_prev) {
        return SignalType::SELL;
    }
    // MACD przecina Signal w górę, gdy oba są poniżej zera.
    if (is_bullish_crossover && macd_curr < 0 && signal_curr < 0) {
        return SignalType::BUY;
    }
    // MACD przecina Signal w dół, gdy oba są powyżej zera.
    if (is_bearish_crossover && macd_curr > 0 && signal_curr > 0) {
        return SignalType::SELL;
    }
    // Przejście MACD powyżej zera często sygnalizuje przejście do trendu wzrostowego.
    if (macd_prev < 0 && macd_curr >= 0) {
        return SignalType::BUY;
    }
    // Przejście MACD poniżej zera często sygnalizuje przejście do trendu spadkowego.
    if (macd_prev > 0 && macd_curr <= 0) {
        return SignalType::SELL;
    }

    return SignalType::NONE;
}