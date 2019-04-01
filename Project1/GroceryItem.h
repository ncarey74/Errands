#pragma once

#include <string>
#include <memory>
#include <vector>

namespace food
{
class GroceryItem
{
public:
    virtual std::string name() const = 0;
};

typedef std::unique_ptr<GroceryItem> GroceryItemPointer;
typedef std::vector<GroceryItemPointer> GroceryItems;
}

