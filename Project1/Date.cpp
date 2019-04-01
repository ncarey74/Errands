#include "Date.h"
#include "stdexcept"

Month::Month(MonthNumber m) : mNumber(m), mName("delay init"), mNumberOfDays(0)
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

/**
 * @todo Custom exception for an invalid date.
 */
Date::Date(Month m, Day d, Year y) : month(m), day(d), year(y)
{
    if (day > month.numberOfDays())
    {
        throw std::logic_error{"Too many days for the month."};
    }
}