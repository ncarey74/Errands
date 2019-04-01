#pragma once

#include "GroceryItem.h"

#include <string>

namespace food
{
class GroceryList
{
public:
    GroceryList();
    ~GroceryList() = default;

    void read() const;
    void crossItemOffList(const std::string& s);
private:
    GroceryItems mList;
    void AddToList(std::string s);
};
}
