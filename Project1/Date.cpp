/*
*   @file   Date.cpp
*   @author Carey Norslien
*   @brief
*/

//---------------------------------------------------------------------------------------------------------------------
// File includes
//---------------------------------------------------------------------------------------------------------------------
#include "Date.h"

#include <sstream>
#include <vector>
#include <queue>
#include <stdexcept>


//---------------------------------------------------------------------------------------------------------------------
// Private helper function definitions
//---------------------------------------------------------------------------------------------------------------------
namespace
{
/**
* @brief
*/
std::istream& operator>>(std::istream& input, MonthNumber& output)
{
    ShortestSafeInteger underlyingValue{};
    input >> underlyingValue;
    output = static_cast<MonthNumber>(underlyingValue);
    return input;
}

/**
* @brief
*/
MonthNumber parsedMonth(const std::string& s)
{
    if (s == "january" || "January")
    {
        return MonthNumber::january;
    }
    else if (s == "feburary" || "Feburary")
    {
        return MonthNumber::february;
    }
    else
    {
        throw std::invalid_argument{ "I am a lazy and bad developer. This month string isn't supported yet." };
    }
}
}

//---------------------------------------------------------------------------------------------------------------------
// Month member function definitions
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 */
Month::Month(const std::string& s)
{
    std::istringstream input{ s };
    MonthNumber m{ MonthNumber::invalid };

    if (input >> m)             // Input is an integral type ("01", "12", etc)
    {
        mNumber = m;
    }
    else                        // Input is a full name ("January", "December", etc)
    {
        mNumber = parsedMonth(s);
    }
    construct(mNumber);
}

/**
 * @brief
 */
Month::Month(MonthNumber m) : mNumber(m)
{
    construct(mNumber);
}

/**
 * @brief
 */
void Month::construct(MonthNumber m)
{
    switch (mNumber)
    {
        case MonthNumber::january:
            finalize("January", 31);
            break;
        case MonthNumber::february:
            finalize("February", 28);
            break;
        case MonthNumber::march:
            finalize("March", 31);
            break;
        case MonthNumber::april:
            finalize("April", 30);
            break;
        case MonthNumber::may:
            finalize("May", 31);
            break;
        case MonthNumber::june:
            finalize("June", 30);
            break;
        case MonthNumber::july:
            finalize("July", 31);
            break;
        case MonthNumber::august:
            finalize("August", 31);
            break;
        case MonthNumber::september:
            finalize("September", 30);
            break;
        case MonthNumber::october:
            finalize("October", 31);
            break;
        case MonthNumber::november:
            finalize("November", 30);
            break;
        case MonthNumber::december:
            finalize("December", 31);
            break;
    }
}

/**
* @brief
*/
void Month::finalize(const std::string& name, Day numberOfDays)
{
    mName = name;
    mNumberOfDays = numberOfDays;
}

/**
* @brief
*/
std::string Month::name() const
{
    return mName;
}

/**
* @brief
*/
Day Month::numberOfDays() const
{
    return mNumberOfDays;
}

/**
* @brief
*/
MonthNumber Month::number() const
{
    return mNumber;
}


//---------------------------------------------------------------------------------------------------------------------
// Date member function definitions
//---------------------------------------------------------------------------------------------------------------------
/**
* @brief
*/
Date::Date(Month m, Day d, Year y) : month(m), day(d), year(y)
{
    if (day > month.numberOfDays())
    {
        day = 0;
    }
}

std::queue<std::string> dateElements(const std::string& s)
{
    std::istringstream input{ s };
    std::queue<std::string> tokens{};
    std::string token{};

    while (getline(input, token, '-'))
    {
        tokens.push(token);
    }

    return tokens;
}

/**
 * @brief
 */
Date::Date(const std::string& s)
{
    std::queue<std::string> tokens{ dateElements(s) };

    std::istringstream monthToken{ tokens.front() };
    tokens.pop();
    std::istringstream dayToken{ tokens.front() };
    tokens.pop();
    std::istringstream yearToken{ tokens.front() };

    MonthNumber monthNumber{};

    monthToken >> monthNumber;
    month = Month{ monthNumber };
    dayToken >> day;
    yearToken >> year;

    std::cout << *this << std::endl;
}


//---------------------------------------------------------------------------------------------------------------------
// Public helper function definitions
//---------------------------------------------------------------------------------------------------------------------
/**
* @brief
*/
std::ostream& operator<<(std::ostream& output, Month& month)
{
    output << month.name();
    return output;
}

/**
* @brief
*/
std::ostream& operator<<(std::ostream& output, Date& date)
{
    output << date.month << " " << date.day << ", " << date.year;
    return output;
}

/**
* @brief
*/
bool operator==(const Month& left, const Month& right)
{
    return left.number() == right.number();
}

/**
* @brief
*/
bool operator!=(const Month& left, const Month& right)
{
    return !(left == right);
}

/**
* @brief
*/
bool operator>(const Month& left, const Month& right)
{
    return left.number() > right.number();
}

/**
* @brief
*/
bool operator<(const Month& left, const Month& right)
{
    return left.number() < right.number();
}

/**
* @brief
*/
bool operator>=(const Month& left, const Month& right)
{
    return left.number() >= right.number();
}

/**
* @brief
*/
bool operator<=(const Month& left, const Month& right)
{
    return left.number() <= right.number();
}

/**
* @brief
*/
bool operator==(const Date& left, const Date& right)
{
    bool sameMonth = (left.month == right.month);
    bool sameDay = (left.day == right.day);
    bool sameYear = (left.year == right.year);
    bool sameDate = sameMonth == true && sameDay == true && sameYear == true;

    return sameDate;
}

/**
* @brief
*/
bool operator!=(const Date& left, const Date& right)
{
    return !(left == right);
}

/**
* @brief
*/
bool operator>(const Date& left, const Date& right)
{
    bool greaterYear = (left.year > right.year);
    bool sameYear = (left.year == right.year);
    bool greaterMonth = (left.month > right.month);
    bool sameMonth = (left.month == right.month);
    bool greaterDay = left.day > right.day;

    if (greaterYear || (sameYear && greaterMonth))
    {
        return true;
    }
    else if (sameYear && sameMonth)
    {
        return greaterDay ? true : false;
    }
    else
    {
        return false;
    }
}

/**
* @brief
*/
bool operator<(const Date& left, const Date& right)
{
    bool lesserYear = left.year < right.year;
    bool sameYear = (left.year == right.year);
    bool lesserMonth = (left.month < right.month);
    bool sameMonth = (left.month == right.month);
    bool lesserDay = left.day < right.day;

    if (lesserYear || (sameYear && lesserMonth))
    {
        return true;
    }
    else if (sameYear && sameMonth)
    {
        return lesserDay ? true : false;
    }
    else
    {
        return false;
    }
}

/**
* @brief
*/
bool operator>=(const Date& left, const Date& right)
{
    bool sameDate = (left == right);
    bool greaterDate = (left > right);

    return sameDate || greaterDate;
}

/**
* @brief
*/
bool operator<=(const Date& left, const Date& right)
{
    bool sameDate = (left == right);
    bool lesserDate = (left < right);

    return sameDate || lesserDate;
}
