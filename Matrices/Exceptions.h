#pragma once

#include <exception>
#include <string>
#include <iostream>

class TooManyColumns : public std::exception
{
public:
   explicit TooManyColumns(const std::string& what);
   virtual const char* what() const throw();

private:
   std::string mErrorMessage{};
};

