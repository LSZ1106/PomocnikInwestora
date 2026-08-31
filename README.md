# Pomocnik Inwestora

Aplikacja desktopowa (Windows Forms, C++/CLI) do **backtestingu strategii giełdowych** opartych na wskaźnikach analizy technicznej. Program wczytuje historyczne dane notowań z pliku CSV, oblicza wskaźniki, symuluje zdefiniowane strategie inwestycyjne na wybranym okresie i prezentuje porównawcze raporty wydajności.

> Projekt powstał jako praca licencjacka.

## Funkcje

- Import historycznych danych giełdowych z plików **CSV** (obsługa pól w cudzysłowach, wartości oddzielonych przecinkami).
- Obliczanie popularnych wskaźników analizy technicznej:
  - **MA** – średnie kroczące (Moving Average),
  - **RSI** – Relative Strength Index (metoda Wildera),
  - **Stochastic Oscillator** (%K / %D),
  - **MACD** – Moving Average Convergence Divergence (linia, sygnał, histogram),
  - **StochRSI** – Stochastic RSI.
- Symulacja i backtesting **5 strategii** inwestycyjnych na zadanym kapitale początkowym i liczbie dni:
  1. MA Crossover (przecięcie dwóch średnich),
  2. RSI (poziomy wyprzedania/wykupienia),
  3. Stochastic (przecięcia %K/%D),
  4. MACD (przecięcia linii i sygnału),
  5. StochRSI.
- Raport wydajności dla każdej strategii: kapitał końcowy, zysk (w punktach i procentach), liczba transakcji oraz transakcji zyskownych.
- Konfigurowalne parametry wskaźników i symulacji (okresy, progi, kapitał początkowy).
- Graficzny interfejs użytkownika w Windows Forms.

## Wymagania

- **Windows** (aplikacja Windows Forms).
- **Visual Studio 2019/2022** z komponentami:
  - „Programowanie aplikacji klasycznych w C++",
  - obsługą **C++/CLI** (Common Language Runtime),
  - **.NET Framework** (Windows Forms).

## Budowanie i uruchamianie

1. Sklonuj repozytorium:
   ```bash
   git clone <adres-repozytorium>
   ```
2. Otwórz plik `PomocnikInwestora.sln` w Visual Studio.
3. Wybierz konfigurację (np. `Debug` / `Release`) oraz platformę (`x64`).
4. Zbuduj rozwiązanie (`Ctrl + Shift + B`).
5. Uruchom aplikację (`F5`).

## Sposób użycia

1. Uruchom aplikację.
2. Wskaż plik CSV z historycznymi danymi notowań.
3. Ustaw parametry wskaźników oraz symulacji (okresy, progi, kapitał początkowy, liczba dni).
4. Uruchom symulację.
5. Przeanalizuj wygenerowane raporty wydajności dla poszczególnych strategii.

## Struktura projektu

| Plik | Opis |
|------|------|
| `CppCLR_WinFormsProject.cpp` | Punkt wejścia aplikacji. |
| `Form1.h` / `Form1.cpp` | Interfejs użytkownika (Windows Forms). |
| `AppLogic.h` | Główna logika: wczytanie danych, obliczenie wskaźników, uruchomienie symulacji. |
| `CzytnikCSV.h` | Parser plików CSV. |
| `DzienAkcji.h` | Model pojedynczego dnia notowań. |
| `MovingAverageIndicator.h` | Średnie kroczące (MA). |
| `RSI.h` | Wskaźnik RSI. |
| `StochasticCalculator.h` | Oscylator stochastyczny. |
| `MACDIndicator.h` | Wskaźnik MACD. |
| `Averages.h` | Funkcje pomocnicze do obliczeń średnich. |
| `signal_generators.h` / `signal_genarators.cpp` | Generatory sygnałów kupna/sprzedaży. |
| `Simulate.h` | Silnik symulacji (backtesting). |
| `PerformanceReport.h` | Struktura raportu wydajności strategii. |
| `ManagedReport.h` | Adapter raportu na typy zarządzane (.NET). |

## Uwagi

Aplikacja ma charakter edukacyjny i demonstracyjny. Wyniki symulacji nie stanowią porady inwestycyjnej.

## Licencja

Projekt udostępniany na licencji MIT – szczegóły w pliku [LICENSE](LICENSE).
