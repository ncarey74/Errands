#include "GroceryExceptions.h"

#include <iostream>

NoList::NoList(const std::string& what) : mErrorMessage(what)
{
    std::cerr << "Could not read file path: " + what;
}

const char* NoList::what() const throw()
{
    return mErrorMessage.c_str();
}

InvalidItem::InvalidItem(const std::string& what) : mErrorMessage(what)
{
    std::cerr << "This can't be found in a grocery store: " + what;
}

const char* InvalidItem::what() const throw()
{
    return mErrorMessage.c_str();
}
