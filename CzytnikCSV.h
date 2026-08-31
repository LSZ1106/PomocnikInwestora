#ifndef CZYTNIKCSV_H
#define CZYTNIKCSV_H
#include <iostream>
#include <string>
#include "DzienAkcji.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <stdexcept> 
#include <locale>   
#include <cctype>  

class CzytnikCSV {
private:
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\v\f\r");
        if (std::string::npos == first) { return str; }
        size_t last = str.find_last_not_of(" \t\n\v\f\r");
        return str.substr(first, (last - first + 1));
    }
    std::vector<std::string> splitCSVQuoted(const std::string& line) {
        std::vector<std::string> result;
        std::stringstream ss(line);
        std::string field;
        bool inQuotes = false;
        char c;
        while (ss.get(c)) {
            if (c == '"') {
                if (inQuotes && ss.peek() == '"') { field += '"'; ss.ignore(); }
                else { inQuotes = !inQuotes; }
            }
            else if (c == ',' && !inQuotes) {
                result.push_back(trim(field)); field.clear();
            }
            else {
                field += c;
            }
        }
        result.push_back(trim(field)); return result;
    }
    std::string decimalCommaToDot(std::string str) {
        str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
        std::replace(str.begin(), str.end(), ',', '.');
        return str;
    }
    double parseDoubleSafe(const std::string& raw_str) {
        std::string cleaned_str = trim(raw_str);
        std::string num_str = decimalCommaToDot(cleaned_str);
        if (num_str.empty()) return 0.0;
        try { return std::stod(num_str); }
        catch (const std::invalid_argument& ia) { throw std::invalid_argument("Nieprawidłowy format liczby double: '" + raw_str + "'"); }
        catch (const std::out_of_range& oor) { throw std::out_of_range("Liczba double poza zakresem: '" + raw_str + "'"); }
    }
    long parseWolumen(std::string raw_s) { 
        std::string s = trim(raw_s); if (s.empty()) return 0; double multiplier = 1.0; char lastChar = '\0';
        if (!s.empty()) {
            lastChar = std::toupper(s.back());
            if (lastChar == 'K') { multiplier = 1000.0; s.pop_back(); }
            else if (lastChar == 'M') { multiplier = 1000000.0; s.pop_back(); }
        }
        s = trim(s); std::string num_str = decimalCommaToDot(s);
        if (num_str.empty() && (lastChar == 'K' || lastChar == 'M')) { throw std::invalid_argument("Brak liczby przed K/M w wolumenie: '" + raw_s + "'"); }
        else if (num_str.empty()) { return 0; }
        try { double value = std::stod(num_str); return static_cast<long>(std::round(value * multiplier)); } 
        catch (const std::invalid_argument& ia) { throw std::invalid_argument("Nieprawidłowy format liczby w wolumenie: '" + raw_s + "'"); }
        catch (const std::out_of_range& oor) { throw std::out_of_range("Liczba w wolumenie poza zakresem: '" + raw_s + "'"); }
    }
    double parseZmiana(std::string raw_s) {
        std::string s = trim(raw_s); if (s.empty()) return 0.0;
        if (!s.empty() && s.back() == '%') { s.pop_back(); }
        s = trim(s); std::string num_str = decimalCommaToDot(s); if (num_str.empty()) return 0.0;
        try { return std::stod(num_str); }
        catch (const std::invalid_argument& ia) { throw std::invalid_argument("Nieprawidłowy format liczby w zmianie: '" + raw_s + "'"); }
        catch (const std::out_of_range& oor) { throw std::out_of_range("Liczba w zmianie poza zakresem: '" + raw_s + "'"); }
    }

    // Funkcja parsowania daty (DD.MM.RRRR)
    DzienAkcji::Date parseDate(const std::string& dateString) {
        std::tm t = {};
        std::stringstream ss(dateString);
        ss >> std::get_time(&t, "%d.%m.%Y"); // Format DD.MM.YYYY
        if (ss.fail()) {
            throw std::runtime_error("Nieprawidłowy format daty: " + dateString);
        }
        return { t.tm_year + 1900, t.tm_mon + 1, t.tm_mday };
    }

public:
    std::vector<DzienAkcji> wczytajDane(const std::string& sciezkaPliku, bool pominNaglowek = true) {
        std::vector<DzienAkcji> akcje;
        std::ifstream file(sciezkaPliku);

        if (!file.is_open()) {
            throw std::runtime_error("Nie można otworzyć pliku CSV: " + sciezkaPliku);
        }

        std::string line;
        if (pominNaglowek && std::getline(file, line)) {} // Pomijamy nagłówek

        int numerLinii = pominNaglowek ? 2 : 1;
        while (std::getline(file, line)) {
            if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
                numerLinii++; continue;
            }

            std::vector<std::string> fields = splitCSVQuoted(line);

            if (fields.size() == 7) {
                try {
                    DzienAkcji::Date parsedDate = parseDate(trim(fields[0]));
                    double ostatnioVal = parseDoubleSafe(fields[1]);
                    double otwarcieVal = parseDoubleSafe(fields[2]);
                    double maksimumVal = parseDoubleSafe(fields[3]);
                    double minimumVal = parseDoubleSafe(fields[4]);
                    long wolumenVal = parseWolumen(fields[5]);
                    double zmianaVal = parseZmiana(fields[6]);

                    akcje.emplace_back(parsedDate, ostatnioVal, otwarcieVal, maksimumVal, minimumVal, wolumenVal, zmianaVal);
                }
                catch (const std::exception& e) {
                    std::cerr << "Błąd parsowania w linii " << numerLinii << ": '" << line << "' - " << e.what() << std::endl;
                }
            }
            else {
                std::cerr << "Ostrzeżenie: Pomięto linię " << numerLinii << " (nieprawidłowa liczba pól: "
                    << fields.size() << "/" << 7 << "): '" << line << "'" << std::endl;
            }
            numerLinii++;
        }
        file.close();
        return akcje;
    }
};
#endif