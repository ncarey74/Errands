#include "Date.h"

#include <sstream>
#include <vector>
#include <tuple>
#include <queue>
#include <stdexcept>


std::istream& operator>>(std::istream& input, MonthNumber& output)
{
    ShortestSafeInteger underlyingValue{};
    input >> underlyingValue;
    output = static_cast<MonthNumber>(underlyingValue);
    return input;
}

std::ostream& operator<<(std::ostream& output, Month& month)
{
    output << month.name();
    return output;
}


//---------------------------------------------------------------------------------------------------------------------
// Month member function definitions
//---------------------------------------------------------------------------------------------------------------------

MonthNumber foo(const std::string& s)
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
        throw std::invalid_argument{"I am a lazy and bad developer. This month string isn't supported yet."};
    }
}

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
        mNumber = foo(s);
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

    std::cout << mName << std::endl;
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

/**
 * @brief
 */
Date::Date(const std::string& s)
{
    std::queue<std::string> tokens{ dateElements(s) };

    auto one = tokens.front();
    std::stringstream monthToken{ one };
    tokens.pop();
    std::stringstream dayToken{ tokens.front() };
    tokens.pop();
    std::stringstream yearToken{ tokens.front() };

    MonthNumber monthNumber{};

    monthToken >> monthNumber;
    month = Month{ monthNumber };
    dayToken >> day;
    yearToken >> year;

    std::cout << "hey!!! " << month << "/" << day << "/" << year << std::endl;
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
