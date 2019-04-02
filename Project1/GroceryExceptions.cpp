#include "GroceryExceptions.h"

#include <iostream>
#include <sstream>


NoList::NoList(const std::string& what)
{
    std::stringstream ss{};
    ss << "Could not read file path " << what;
    mErrorMessage = ss.str();
}

const char* NoList::what() const throw()
{
    return mErrorMessage.c_str();
}

InvalidItem::InvalidItem(const std::string& what)
{
    std::stringstream ss{};
    ss << "Invalid item: " << what;
    mErrorMessage = ss.str();
}

const char* InvalidItem::what() const throw()
{
    return mErrorMessage.c_str();
}
