#pragma once
// ManagedReport.h
#pragma once

// Pamiętaj o dyrektywach NOMINMAX i NO_SYS_HEADERS w pch.h, jeśli ich używasz
// Ten plik powinien zawierać tylko niezbędne include.

using namespace System; // Do String i innych typów CLR
using namespace System::Collections::Generic; // Jeśli używasz List<T>
using namespace System::ComponentModel; // Dla DisplayNameAttribute i innych atrybutów

// Forward declaration, jeśli klasa TradingAppLogic będzie korzystać z tej klasy
// ref class TradingAppLogic; // NIEpotrzebne, ta klasa jest niezależna

// Definicja zarządzanej klasy, która będzie reprezentować wiersz w DataGridView
public ref class StrategyPerformanceReportManaged {
public:
    // Używamy String^ dla nazw, a double dla wartości liczbowych
    // Możesz użyć atrybutu DisplayName, aby nazwy kolumn były ładniejsze
    [DisplayName("Strategia")]
        property String^ IndicatorName;

    [DisplayName("Kapitał Początkowy")]
        property double InitialCapital;

    [DisplayName("Kapitał Końcowy")]
        property double FinalCapital;

    [DisplayName("Zysk (%)")]
        property double PercentageGain;

    [DisplayName("Zysk (pkt)")]
        property double TotalProfitPoints;

    [DisplayName("Straty (pkt)")]
        property double TotalLossPoints;

    [DisplayName("Transakcje")]
        property int TotalTrades;

    [DisplayName("Wygrane")]
        property int WinningTrades;

    [DisplayName("Przegrane")]
        property int LosingTrades;

    [DisplayName("Max Obsunięcie (%)")]
        property double MaxDrawdownPercentage;

    [DisplayName("Max Obsunięcie (pkt)")]
        property double MaxDrawdownPoints;

    // Możesz dodać konstruktor, aby łatwo przekształcić natywny raport
    StrategyPerformanceReportManaged(const StrategyPerformanceReport& nativeReport) {
        // Konwersja std::string do System::String^
        msclr::interop::marshal_context context; // Pamiętaj o include <msclr/marshal_cppstd.h> w pliku .cpp gdzie to używasz

        IndicatorName = context.marshal_as<String^>(nativeReport.indicatorName);
        InitialCapital = nativeReport.initialCapital;
        FinalCapital = nativeReport.finalCapital;
        PercentageGain = nativeReport.percentageGain;
        TotalProfitPoints = nativeReport.totalProfitPoints;
       //TotalLossPoints = nativeReport.totalLossPoints;
        TotalTrades = nativeReport.totalTrades;
        WinningTrades = nativeReport.winningTrades;
       // LosingTrades = nativeReport.losingTrades;
        //MaxDrawdownPercentage = nativeReport.maxDrawdownPercentage;
       // MaxDrawdownPoints = nativeReport.maxDrawdownPoints;
    }
};