#pragma once

#include "GroceryItem.h"

namespace food
{
class Fruit : public GroceryItem
{
public:
    virtual std::string name() const = 0;
    virtual Date expirationDate() const = 0;
};


/**
 * @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
 *           A VS2013 bug prevents these two functions from being declared as default.
 */
class Apple : public Fruit
{
public:
    Apple() = default;
    ~Apple() = default;
    Apple(const Apple&) = default;
    Apple& operator=(const Apple&) = default;

    std::string name() const;
    Date expirationDate() const;
private:
    std::string mName = "apple";
    Date mExpirationDate{"06-09-2020"};
};


/**
* @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
*           A VS2013 bug prevents these two functions from being declared as default.
*/
class Peach : public virtual Fruit
{
public:
    Peach() = default;
    ~Peach() = default;
    Peach(const Peach&) = default;
    Peach& operator=(const Peach&) = default;

    std::string name() const;
    Date expirationDate() const;
private:
    std::string mName = "peach";
    Date mExpirationDate{};
};


/**
* @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
*           A VS2013 bug prevents these two functions from being declared as default.
*/
class Pear : public virtual Fruit
{
public:
    Pear() = default;
    ~Pear() = default;
    Pear(const Pear&) = default;
    Pear& operator=(const Pear&) = default;

    std::string name() const;
    Date expirationDate() const;
private:
    std::string mName = "pear";
    Date mExpirationDate{};
};


/**
* @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
*           A VS2013 bug prevents these two functions from being declared as default.
*/
class Banana : public virtual Fruit
{
public:
    Banana() = default;
    ~Banana() = default;
    Banana(const Banana&) = default;
    Banana& operator=(const Banana&) = default;

    std::string name() const;
    Date expirationDate() const;
private:
    std::string mName = "banana";
    Date mExpirationDate{};
};
}
