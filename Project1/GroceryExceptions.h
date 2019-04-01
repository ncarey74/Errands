#pragma once

#include <exception>
#include <string>
#include <iostream>

class NoList : public std::exception
{
public:
    explicit NoList(const std::string& what);
    virtual const char* what() const throw();

private:
    std::string mErrorMessage{};
};

class InvalidItem : public std::exception
{
public:
    explicit InvalidItem(const std::string& what);
    virtual const char* what() const throw();

private:
    std::string mErrorMessage{};
};
