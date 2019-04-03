#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Date.h"

namespace food
{
class GroceryItem
{
public:
    virtual std::string name() const = 0;
    virtual Date expirationDate() const = 0;
};

typedef std::unique_ptr<GroceryItem> GroceryItemPointer;
typedef std::vector<GroceryItemPointer> GroceryItems;
}

