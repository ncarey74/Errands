#pragma once

#include <string>

typedef unsigned char Day;
typedef unsigned int Year;

enum class MonthNumber : unsigned char
{
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
    MonthNumber mNumber;
    std::string mName;
    Day mNumberOfDays;
};

struct Date
{
    Month month;
    Day day;
    Year year;

    explicit Date(Month m, Day d, Year y);
};