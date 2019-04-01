#include "GroceryExceptions.h"
#include "GroceryList.h"

#include <iostream>

void rageAtLife()
{
    std::cerr << "Where did I put that list?" << std::endl;
}

void rageAtTheStore()
{
    std::cerr << "Why don't they have the things I need!" << std::endl;
    std::cerr << "Manager, this is unacceptable!" << std::endl;
}

int main()
{
    try
    {
        food::GroceryList g{};
        g.read();
    }
    catch (const NoList& e)
    {
        rageAtLife();
    }
    catch (const InvalidItem& e)
    {
        rageAtTheStore();
    }

    //holdIt();

    return 0;
}
