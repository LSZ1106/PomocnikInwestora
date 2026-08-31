#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <sstream> 
#include <map>     
#include <ctime>
#include <fstream> 

class DzienAkcji {
public:
    struct Date {
        int year;
        int month;
        int day;

        // Metoda pomocnicza do porównywania dat
        bool operator>(const Date& other) const {
            if (year != other.year) return year > other.year;
            if (month != other.month) return month > other.month;
            return day > other.day;
        }
        bool operator<(const Date& other) const {
            if (year != other.year) return year < other.year;
            if (month != other.month) return month < other.month;
            return day < other.day;
        }
        bool operator>=(const Date& other) const { return !(*this < other); }
        bool operator<=(const Date& other) const { return !(*this > other); }
        bool operator==(const Date& other) const {
            return year == other.year && month == other.month && day == other.day;
        }

        // Konwersja na string w formacie DD.MM.RRRR
        std::string toString() const {
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(2) << day << "."
                << std::setfill('0') << std::setw(2) << month << "."
                << year;
            return ss.str();
        }

        Date addDays(int days) const {
            std::tm t = {};
            t.tm_mday = day;
            t.tm_mon = month - 1; // tm_mon jest 0-indeks 
            t.tm_year = year - 1900; // tm_year to lata od 1900 r.
            std::time_t time_temp = std::mktime(&t);
            if (time_temp == -1) {
                throw std::runtime_error("Invalid date conversion.");
            }
            time_temp += days * 24 * 60 * 60; 
            std::tm* new_t = std::localtime(&time_temp);
            return { new_t->tm_year + 1900, new_t->tm_mon + 1, new_t->tm_mday };
        }
    };

private:
    Date data;
    double ostatnio;
    double otwarcie;
    double maksimum;
    double minimum;
    long wolumen; 
    double zmiana;

public:
    DzienAkcji() : data({ 0,0,0 }), ostatnio(0.0), otwarcie(0.0),
        maksimum(0.0), minimum(0.0), wolumen(0), zmiana(0.0) {}

    DzienAkcji(Date d, double ost, double otw, double max, double min, long vol, double zm)
        : data(d), ostatnio(ost), otwarcie(otw), maksimum(max), minimum(min), wolumen(vol), zmiana(zm) {}

 
    void setData(Date newData) { this->data = newData; }
    void setOstatnio(double newOstatnio) {
        if (newOstatnio < 0) { throw std::invalid_argument("Wartość 'ostatnio' nie może być ujemna."); }
        ostatnio = newOstatnio;
    }
    void setOtwarcie(double newOtwarcie) {
        if (newOtwarcie < 0) { throw std::invalid_argument("Wartość 'otwarcie' nie może być ujemna."); }
        otwarcie = newOtwarcie;
    }
    void setMaksimum(double newMaksimum) {
        if (newMaksimum < 0) { throw std::invalid_argument("Wartość 'maksimum' nie może być ujemna."); }
        maksimum = newMaksimum;
    }
    void setMinimum(double newMinimum) {
        if (newMinimum < 0 || (maksimum != 0.0 && newMinimum > maksimum)) {
            throw std::invalid_argument("Nieprawidłowa wartość 'minimum'.");
        }
        minimum = newMinimum;
    }
    void setWolumen(long newWolumen) {
        if (newWolumen < 0) {
            std::cerr << "Ostrzeżenie: Próba ustawienia ujemnego wolumenu (" << newWolumen << "). Ustawiono 0." << std::endl;
            wolumen = 0;
            throw std::invalid_argument("Wolumen nie może być ujemny.");
        }
        else {
            wolumen = newWolumen;
        }
    }
    void setZmiana(double newZmiana) { zmiana = newZmiana; }

    Date getData() const { return data; }
    double getOstatnio() const { return ostatnio; }
    double getOtwarcie() const { return otwarcie; }
    double getMax() const { return maksimum; }
    double getMin() const { return minimum; }
    long getWol() const { return wolumen; }
    double getZmiana() const { return zmiana; }

    // Metody pomocnicze
    void wyswietl() const {
        std::cout << "Data = " << data.toString()
            << ": Ostatnio = " << ostatnio << ", Otwarcie = " << otwarcie
            << ", Maksimum = " << maksimum << ", Minimum = " << minimum
            << ", Wolumen = " << wolumen << ", Zmiana = " << zmiana << "%\n";
    }
};