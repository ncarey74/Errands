#include "Date.h"

#include <sstream>
#include <vector>
#include <tuple>
#include <queue>


std::istream& operator>>(std::istream& input, MonthNumber& output)
{
    unsigned char underlyingValue{};
    input >> underlyingValue;
    output = static_cast<MonthNumber>(underlyingValue);
    return input;
}


//---------------------------------------------------------------------------------------------------------------------
// Month member function definitions
//---------------------------------------------------------------------------------------------------------------------

Month::Month(std::string s)
{

}

Month::Month(MonthNumber m) : mNumber(m)
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

void Month::finalize(const std::string& name, Day numberOfDays)
{
    mName = name;
    mNumberOfDays = numberOfDays;
}

std::string Month::name() const
{
    return mName;
}

Day Month::numberOfDays() const
{
    return mNumberOfDays;
}

MonthNumber Month::number() const
{
    return mNumber;
}


//---------------------------------------------------------------------------------------------------------------------
// Date member function definitions
//---------------------------------------------------------------------------------------------------------------------

Date::Date(Month m, Day d, Year y) : month(m), day(d), year(y)
{
    if (day > month.numberOfDays())
    {
        throw InvalidDate{month, day};
    }
}

std::queue<std::string> dateElements(const std::string& s)
{
    std::stringstream input{ s };
    std::queue<std::string> tokens{};
    std::string token{};

    while (getline(input, token, '-'))
    {
        tokens.push(token);
    }

    return tokens;
}

Date::Date(const std::string& s)
{
    std::queue<std::string> tokens{ dateElements(s) };

    std::stringstream monthToken{ tokens.front() };
    tokens.pop();
    std::stringstream dayToken{ tokens.front() };
    tokens.pop();
    std::stringstream yearToken{ tokens.front() };

    MonthNumber monthNumber{};

    monthToken >> monthNumber;
    month = Month{ monthNumber };
    dayToken >> day;
    yearToken >> year;
}


//---------------------------------------------------------------------------------------------------------------------
// InvalidDate member function definitions
//---------------------------------------------------------------------------------------------------------------------

InvalidDate::InvalidDate(Month m, Day d)
{
    std::stringstream ss{};
    ss << "Invalid Data Exception: " << m.name() << "doesn't have day " << d;
    mErrorMessage = ss.str();;
}

const char* InvalidDate::what() const throw()
{
    return mErrorMessage.c_str();
}
