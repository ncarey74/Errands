#include "GroceryExceptions.h"
#include "GroceryList.h"
#include "Date.h"

#include <iostream>

void holdIt()
{
    char c{};
    std::cin >> c;
}

void rageAtLife(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    std::cerr << "Where did I put that list?" << std::endl;
    holdIt();
}

void rageAtTheStore(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    std::cerr << "Why don't they have the things I need!" << std::endl;
    std::cerr << "Manager, this is unacceptable!" << std::endl;
    holdIt();
}

void testDates()
{
    Date today{ "04-07-2019" };
    Date tomorrow{ "04-08-2019" };
    Date yesterday{ "04-06-2019" };
    Date aYearAgo{ "04-07-2018" };
    Date lastMonth{ "03-07-2019" };
    Date nextYear{ "04-07-2020" };
    Date nextMonth{ "05-07-2019" };

    //---
    if ((today != tomorrow) && (today != yesterday))
    {
        std::cout << "yay! inequality works" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! inequality didn't work" << std::endl;
    }

    //---
    if (today < tomorrow)
    {
        std::cout << "yay! today is less than tomorrow" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't less than tomorrow" << std::endl;
    }

    //---
    if (today > yesterday)
    {
        std::cout << "yay! today is greater than yesterday" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't greater than yesterday" << std::endl;
    }

    //---
    if (today > aYearAgo)
    {
        std::cout << "yay! today is greater than a year ago" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't greater than a year ago" << std::endl;
    }

    //---
    if (today > lastMonth)
    {
        std::cout << "yay! today is greater than last month" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't greater than last month" << std::endl;
    }

    //---
    if (today < nextYear)
    {
        std::cout << "yay! today is less than a year from now" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't less than a year from now" << std::endl;
    }

    //---
    if (today < nextMonth)
    {
        std::cout << "yay! today is less than next month" << std::endl;
    }
    else
    {
        std::cerr << "uh oh! today isn't less than next month" << std::endl;
    }
}

int main()
{
    try
    {
        food::GroceryList g{};
        g.read();
        g.crossItemOffList("apple");
        g.read();

        testDates();
    }
    catch (const NoList& e)
    {
        rageAtLife(e);
    }
    catch (const InvalidItem& e)
    {
        rageAtTheStore(e);
    }

    //holdIt();

    return 0;
}
