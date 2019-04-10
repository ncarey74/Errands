/*
*   @file   Date.cpp
*   @author Carey Norslien
*   @brief  Defines the classes and functions needed to use calendar dates.
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
// Private class definitions
//---------------------------------------------------------------------------------------------------------------------
namespace
{
/**
* @brief Exception for when too many elements are added to a container.
*/
class TooManyElements : public std::exception
{
public:
    explicit TooManyElements(const std::string& what);
    virtual const char* what() const throw();

private:
    std::string mErrorMessage{};
};

/**
* @brief
*/
TooManyElements::TooManyElements(const std::string& what)
{
    std::ostringstream ss{};
    ss << "Too many elements were added to container type: " << what;
    mErrorMessage = ss.str();
}

/**
* @brief
*/
const char* TooManyElements::what() const throw()
{
    return mErrorMessage.c_str();
}

/**
* @brief    Container of parsed date string tokens.
* @details  Assumes order of month, day, year. This class is to be used internally for the Date class.
*/
class DateElements
{
public:
    void add(std::string s);
    std::string get();
private:
    std::queue<std::string> mQueue;
};

/**
* @brief        Adds a token from the date string input.
* @param[in]    s   Token from the string input (month, day, or year)
* @throw        TooManyElements if a token was added beyond month, day, and year.
*/
void DateElements::add(std::string s)
{
    if (mQueue.size() < 3)
    {
        mQueue.push(s);
    }
    else
    {
        throw TooManyElements{ "DateElements" };
    }
}

/**
* @brief
*/
std::string DateElements::get()
{
    if (mQueue.empty() == false)
    {
        auto element = mQueue.front();
        mQueue.pop();
        return element;
    }
    else
    {
        return "0";
    }
}
}


//---------------------------------------------------------------------------------------------------------------------
// Private helper function definitions
//---------------------------------------------------------------------------------------------------------------------
namespace
{
/**
* @brief        Allows an input stream to set the value of the month number.
* @note         Not a valid operation outside of this file.
* @param[in]    input   laziness
* @param[out]   output  laziness
* @return       The input stream.
*/
std::istream& operator>>(std::istream& input, MonthNumber& output)
{
    ShortestSafeInteger underlyingValue{};
    input >> underlyingValue;
    output = static_cast<MonthNumber>(underlyingValue);
    return input;
}

/**
* @brief        Parses the integral representation of the month from the string input.
* @note         Not a valid operation outside of this file.
* @param[in]    s   The name of the month.
* @return       The integral representation of the month.
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

/**
* @brief        Given a date string, returns the month, day, and year values.
* @param[in]    The date string in the format of "mm-dd-yyyy".
* @return       The month, day, and year values contained in a queue to enforce the order.
* @todo         Handle poorly formated date string.
*/
DateElements dateElements(const std::string& s)
{
    std::istringstream input{ s };
    DateElements tokens{};
    std::string token{};

    while (getline(input, token, '-'))
    {
        tokens.add(token);
    }

    return tokens;
}
}


//---------------------------------------------------------------------------------------------------------------------
// Month member function definitions
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief       Constructs a Month from a string input.
 * @param[in]   s   The name of the month.
 */
Month::Month(const std::string& s)
{
    std::istringstream input{ s };
    MonthNumber m{ MonthNumber::invalid };

    if (input >> m)             // Input is an integral type ("01", "12", etc)
    {
        mCalendarPosition = m;
    }
    else                        // Input is a full name ("January", "December", etc)
    {
        mCalendarPosition = parsedMonth(s);
    }
    construct(mCalendarPosition);
}

/**
 * @brief       Constructs a Month from its integral representation.
 * @param[in]   m   The integral representation of the month.
 */
Month::Month(MonthNumber m) : mCalendarPosition(m)
{
    construct(mCalendarPosition);
}

/**
 * @brief       Begins construction of the Month.
 * @detail      The details of a month, such as its string representation and the number of days in a month, can be
 *              constructed from the month's position in the calendar. 
 * @param[in]   m   The month's position in the calendar.
 */
void Month::construct(MonthNumber m)
{
    switch (mCalendarPosition)
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
* @brief        Finishes the construction of the Month.
* @param[in]    name            The standardized string representation of the month.
* @param[in]    numberOfDays    The number of days in a month.
*/
void Month::finalize(const std::string& name, Day numberOfDays)
{
    mName = name;
    mNumberOfDays = numberOfDays;
}

/**
* @return   The string representation of the month.
*/
std::string Month::name() const
{
    return mName;
}

/**
* @return   The number of days in the month.
*/
Day Month::numberOfDays() const
{
    return mNumberOfDays;
}

/**
* @return   The calendar position of the month.
*/
MonthNumber Month::calendarPosition() const
{
    return mCalendarPosition;
}


//---------------------------------------------------------------------------------------------------------------------
// Date member function definitions
//---------------------------------------------------------------------------------------------------------------------
/**
* @brief        Constructs the date from the month, day, and year.
* @details      If a month is not valid, then use the default values of zero month, zero day, and zero year.
* @param[in]    m   Month
* @param[in]    d   Day
* @param[in]    y   Year
*/
Date::Date(Month m, Day d, Year y) : mMonth(m), mDay(d), mYear(y)
{
    if (mDay > mMonth.numberOfDays())
    {
        mDay = 0;
        mYear = 0;
    }
}

/**
 * @brief       Constructs the date from a date string in the format "mm-dd-yyyy".
 * @param[in]   s   Date string formated "mm-dd-yyyy".
 */
Date::Date(const std::string& s)
{
    DateElements tokens{ dateElements(s) };

    std::istringstream monthToken{ tokens.get() };
    std::istringstream dayToken{ tokens.get() };
    std::istringstream yearToken{ tokens.get() };

    MonthNumber monthNumber{};

    monthToken >> monthNumber;
    mMonth = Month{ monthNumber };
    dayToken >> mDay;
    yearToken >> mYear;

    std::cout << *this << std::endl;
}

/**
* @return   The month.
*/
Month Date::month() const
{
    return mMonth;
}

/**
* @return   The day.
*/
Day Date::day() const
{
    return mDay;
}

/**
* @return   The year.
*/
Year Date::year() const
{
    return mYear;
}


//---------------------------------------------------------------------------------------------------------------------
// Public helper function definitions
//---------------------------------------------------------------------------------------------------------------------
/**
* @brief        Outputs the month, such as "January" or "December".
* @param[in]    output  laziness
* @param[in]    month   The month to output.
* @return       laziness
*/
std::ostream& operator<<(std::ostream& output, Month& month)
{
    output << month.name();
    return output;
}

/**
* @brief        Outputs the date, such as "January 01, 2000" or "December 31, 2999".
* @param[in]    output  laziness
* @param[in]    month   The date to output.
* @return       laziness
*/
std::ostream& operator<<(std::ostream& output, Date& date)
{
    output << date.month() << " " << date.day() << ", " << date.year();
    return output;
}

/**
* @brief        Equality operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator==(const Month& left, const Month& right)
{
    return left.calendarPosition() == right.calendarPosition();
}

/**
* @brief    Inequality operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator!=(const Month& left, const Month& right)
{
    return !(left == right);
}

/**
* @brief        Greater than operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator>(const Month& left, const Month& right)
{
    return left.calendarPosition() > right.calendarPosition();
}

/**
* @brief        Less than operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator<(const Month& left, const Month& right)
{
    return left.calendarPosition() < right.calendarPosition();
}

/**
* @brief        Greater than or equal to operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator>=(const Month& left, const Month& right)
{
    return left.calendarPosition() >= right.calendarPosition();
}

/**
* @brief        Less than or equal to operator for months.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator<=(const Month& left, const Month& right)
{
    return left.calendarPosition() <= right.calendarPosition();
}

/**
* @brief        Equality operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator==(const Date& left, const Date& right)
{
    bool sameMonth = (left.month() == right.month());
    bool sameDay = (left.day() == right.day());
    bool sameYear = (left.year() == right.year());
    bool sameDate = (sameMonth == true) && (sameDay == true) && (sameYear == true);

    return sameDate;
}

/**
* @brief        Inequality operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator!=(const Date& left, const Date& right)
{
    return !(left == right);
}

/**
* @brief        Greater than operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator>(const Date& left, const Date& right)
{
    bool greaterYear = (left.year() > right.year());
    bool sameYear = (left.year() == right.year());
    bool greaterMonth = (left.month() > right.month());
    bool sameMonth = (left.month() == right.month());
    bool greaterDay = (left.day() > right.day());

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
* @brief        Less than operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator<(const Date& left, const Date& right)
{
    bool sameDate = (left == right);
    bool greaterDate = (left > right);

    return !sameDate && !greaterDate;
}

/**
* @brief        Greater than or equal to operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator>=(const Date& left, const Date& right)
{
    bool sameDate = (left == right);
    bool greaterDate = (left > right);

    return sameDate || greaterDate;
}

/**
* @brief        Less than or equal to operator for dates.
* @param[in]    left    lazy
* @param[in]    right   lazy
* @return       lazy
*/
bool operator<=(const Date& left, const Date& right)
{
    bool sameDate = (left == right);
    bool lesserDate = (left < right);

    return sameDate || lesserDate;
}
