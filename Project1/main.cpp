#include "GroceryExceptions.h"
#include "GroceryList.h"

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

int main()
{
    try
    {
        food::GroceryList g{};
        g.read();
        g.crossItemOffList("apple");
        g.read();
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
