#pragma once

#include <string>
#include <exception>

typedef unsigned char Day;
typedef unsigned int Year;

enum class MonthNumber : unsigned char
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

    std::string name() const;
    Day numberOfDays() const;
    MonthNumber number() const;

private:
    MonthNumber mNumber{MonthNumber::invalid};
    std::string mName = "Invalid month";
    Day mNumberOfDays{0};
};

struct Date
{
    Month month{MonthNumber::invalid};
    Day day{0};
    Year year{0};

    explicit Date(Month m, Day d, Year y);
};

class InvalidDate : public std::exception
{
public:
    explicit InvalidDate(Month m, Day d);
    virtual const char* what() const throw();

private:
    std::string mErrorMessage{};
};