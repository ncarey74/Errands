#include "Exceptions.h"

#include <iostream>
#include <sstream>


TooManyColumns::TooManyColumns(const std::string& what)
{
   std::stringstream ss{};
   ss << "Attempted to add too many columns to the matrix. Tried to add " << what << " columns!";
   mErrorMessage = ss.str();
}

const char* TooManyColumns::what() const throw()
{
   return mErrorMessage.c_str();
}

TooManyRows::TooManyRows(const std::string& what)
{
   std::stringstream ss{};
   ss << "Attempted to add too many rows to the matrix. Tried to add " << what << " rows!";
   mErrorMessage = ss.str();
}

const char* TooManyRows::what() const throw()
{
   return mErrorMessage.c_str();
}
