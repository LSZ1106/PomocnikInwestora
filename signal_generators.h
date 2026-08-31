#ifndef SIGNAL_GENERATORS_H
#define SIGNAL_GENERATORS_H

#include <string>
#include <cmath> 
enum class SignalType {
    BUY,
    SELL,
    HOLD,
    NONE  
};
namespace TradingSignals {
    std::string signalTypeToString(SignalType signal);
    SignalType getMACrossoverAction(double ma_short_curr, double ma_long_curr,
        double ma_short_prev, double ma_long_prev,
        double price_curr, double price_prev);

    SignalType getRSIAction(double rsi_curr, double rsi_prev,
        double oversold_threshold, double overbought_threshold,
        double price_curr, double price_prev);
    SignalType getOscillatorCrossoverAction(
        double k_curr, double d_curr,
        double k_prev, double d_prev,
        double oversold_threshold, double overbought_threshold);

    SignalType getStochasticAction(double k_curr, double d_curr,
        double k_prev, double d_prev,
        double oversold = 20.0, double overbought = 80.0);

    SignalType getStochRSIAction(double k_curr, double d_curr,
        double k_prev, double d_prev,
        double oversold = 20.0, double overbought = 80.0);

    SignalType  getMACDAction(
        double macd_curr, double signal_curr, double histogram_curr, 
        double macd_prev, double signal_prev, double histogram_prev );
   
};
#endif 