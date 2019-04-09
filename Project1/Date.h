/*
*   @file   Date.h
*   @author Carey Norslien
*   @brief  
*/
#pragma once


//---------------------------------------------------------------------------------------------------------------------
// File includes
//---------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>


//---------------------------------------------------------------------------------------------------------------------
// Public type declarations
//---------------------------------------------------------------------------------------------------------------------
// `unsigned char` had unexpected behavior when parsing string, so use `unsigned short`
typedef unsigned short ShortestSafeInteger;
typedef ShortestSafeInteger Day;
typedef ShortestSafeInteger Year;


//---------------------------------------------------------------------------------------------------------------------
// Class declarations
//---------------------------------------------------------------------------------------------------------------------
/**
* @brief    The number of the month in the calendar year.
*/
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


/*
* @brief    The month in a date.
* @details  Enforces the validity of months. A month must exist in the calendar year, and a month has the correct
*           number of days.
* @warning  Does not enforce leap years. February is always 28 days.
*/
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


/*
* @brief    The date in the format of month-day-year.
* @details  Allows the date to be any arrangement of month-day-year (year-month-day, etc...). Enforces valid dates;
*           the specified day is part of the specified month. A default date will have zero'd member data. Invalid
*           input will produce a default date.
* @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
*           A VS2013 bug prevents these two functions from being declared as default.
* @todo     Consider if the design should allow for default dates with zero'd member data. If not, then an invalid date
*           should throw an exception.
*/
class Date
{
public:
    explicit Date(Month m, Day d, Year y);
    explicit Date(const std::string& s);
    Date() = default;
    ~Date() = default;
    Date(const Date&) = default;
    Date& operator=(const Date&) = default;

    Month month() const;
    Day day() const;
    Year year() const;
private:
    Month mMonth{ MonthNumber::invalid };
    Day mDay{ 0 };
    Year mYear{ 0 };
};


//---------------------------------------------------------------------------------------------------------------------
// Public helper function declarations
//---------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& output, Month& month);
bool operator==(const Month& left, const Month& right);
bool operator!=(const Month& left, const Month& right);
bool operator>(const Month& left, const Month& right);
bool operator<(const Month& left, const Month& right);
bool operator>=(const Month& left, const Month& right);
bool operator<=(const Month& left, const Month& right);

std::ostream& operator<<(std::ostream& output, Date& date);
bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);
bool operator>(const Date& left, const Date& right);
bool operator<(const Date& left, const Date& right);
bool operator>=(const Date& left, const Date& right);
bool operator<=(const Date& left, const Date& right);
