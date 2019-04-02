#include "Date.h"

#include "stdexcept"
#include <iostream>
#include <sstream>

void Month::finalize(const std::string& name, Day numberOfDays)
{
    mName = name;
    mNumberOfDays = numberOfDays;
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

Date::Date(Month m, Day d, Year y) : month(m), day(d), year(y)
{
    if (day > month.numberOfDays())
    {
        throw InvalidDate{month, day};
    }
}

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
