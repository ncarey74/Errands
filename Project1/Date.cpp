#include "Date.h"

#include "stdexcept"
#include <iostream>
#include <sstream>

Month::Month(MonthNumber m) : mNumber(m)
{
    switch (mNumber)
    {
        case MonthNumber::january:
            mName = "January";
            mNumberOfDays = 31;
            break;
        case MonthNumber::february:
            mName = "February";
            mNumberOfDays = 28;
            break;
        case MonthNumber::march:
            mName = "March";
            mNumberOfDays = 31;
            break;
        case MonthNumber::april:
            mName = "April";
            mNumberOfDays = 30;
            break;
        case MonthNumber::may:
            mName = "May";
            mNumberOfDays = 31;
            break;
        case MonthNumber::june:
            mName = "June";
            mNumberOfDays = 30;
            break;
        case MonthNumber::july:
            mName = "July";
            mNumberOfDays = 31;
            break;
        case MonthNumber::august:
            mName = "August";
            mNumberOfDays = 31;
            break;
        case MonthNumber::september:
            mName = "September";
            mNumberOfDays = 30;
            break;
        case MonthNumber::october:
            mName = "October";
            mNumberOfDays = 31;
            break;
        case MonthNumber::november:
            mName = "November";
            mNumberOfDays = 30;
            break;
        case MonthNumber::december:
            mName = "December";
            mNumberOfDays = 31;
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
