#pragma once

#include <string>
#include <exception>
#include <iostream>

// `unsigned char` had unexpected behavior when parsing string, so use `unsigned short`
typedef unsigned short ShortestSafeInteger;
typedef ShortestSafeInteger Day;
typedef ShortestSafeInteger Year;

enum class MonthNumber : ShortestSafeInteger
{
    invalid     = 0,
    january     = 1,
    february    = 2,
    march       = 3,
    april       = 4,
    may         = 5,
    june        = 6,
    july        = 7,
    august      = 8,
    september   = 9,
    october     = 10,
    november    = 11,
    december    = 12
};


class Month
{
public:
    explicit Month(MonthNumber m);
    explicit Month(const std::string& s);

    std::string name() const;
    Day numberOfDays() const;
    MonthNumber number() const;

private:
    MonthNumber mNumber{ MonthNumber::invalid };
    std::string mName = "Invalid month";
    Day mNumberOfDays{ 0 };

    void construct(MonthNumber m);
    void finalize(const std::string& name, Day numberOfDays);
};


struct Date
{
    Month month{ MonthNumber::invalid };
    Day day{ 0 };
    Year year{ 0 };

    explicit Date(Month m, Day d, Year y);
    explicit Date(const std::string& s);
    Date() = default;
};


class InvalidDate : public std::exception
{
public:
    explicit InvalidDate(Month m, Day d);
    virtual const char* what() const throw();

private:
    std::string mErrorMessage{};
};

std::istream& operator>>(std::istream& input, MonthNumber& output);
std::ostream& operator<<(std::ostream& output, Month& month);
