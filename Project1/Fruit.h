#pragma once

#include "GroceryItem.h"

namespace food
{
class Fruit : public GroceryItem
{
public:
    virtual std::string name() const = 0;
};

class Apple : public Fruit
{
public:
    Apple() = default;
    ~Apple() = default;
    Apple(const Apple&) = default;
    Apple& operator=(const Apple&) = default;
    // Apple(const Apple&&) = default;  <-- VS2013 bug prevents move constructors from being explictly defined as default
    // Apple& operator=(const Apple&&) = default;  <-- VS2013 bug
    std::string name() const;
private:
    std::string mName = "apple";
};

class Peach : public virtual Fruit
{
public:
    Peach() = default;
    ~Peach() = default;
    Peach(const Peach&) = default;
    Peach& operator=(const Peach&) = default;
    // Peach(const Peach&&) = default;  <-- VS2013 bug prevents move constructors from being explictly defined as default
    // Peach& operator=(const Peach&&) = default;  <-- VS2013 bug
    std::string name() const;
private:
    std::string mName = "peach";
};


class Pear : public virtual Fruit
{
public:
    Pear() = default;
    ~Pear() = default;
    Pear(const Pear&) = default;
    Pear& operator=(const Pear&) = default;
    // Pear(const Pear&&) = default;  <-- VS2013 bug prevents move constructors from being explictly defined as default
    // Pear& operator=(const Pear&&) = default;  <-- VS2013 bug
    std::string name() const;
private:
    std::string mName = "pear";
};
}
