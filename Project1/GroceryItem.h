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

//bool operator==(const GroceryItem& lhs, const GroceryItem& rhs)
//{
//    return lhs.name() == rhs.name();
//}

typedef std::unique_ptr<GroceryItem> GroceryItemPointer;
typedef std::vector<GroceryItemPointer> GroceryItems;
}
