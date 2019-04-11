#pragma once

#include "PlainStruct.h"

#include <vector>
#include <memory>
#include <utility>

/**
* @brief    Base class
* @remark   All children will simply return an integer, but VS2013 was being dumb so make this an abstract base class.
*/
class Animal
{
public:
    virtual int id() = 0;
};

/**
* @brief    Subclass
*/
class Cat : public Animal
{
public:
    Cat() = default;
    ~Cat() = default;
    Cat(const Cat&) = default;
    Cat& operator=(const Cat&) = default;
    int id() { return mId; }
private:
    int mId{ 1 };
};

/**
* @brief    Subclass
*/
class Dog : public Animal
{
public:
    Dog() = default;
    ~Dog() = default;
    Dog(const Dog&) = default;
    Dog& operator=(const Dog&) = default;
    int id() { return mId; }
private:
    int mId{ 2 };
};

typedef std::unique_ptr<Animal> AnimalPointer;
typedef std::vector<AnimalPointer> AnimalKingdom;

/**
* @brief    The composite class that can be turned into a POD struct.
*/
class CompositeClass
{
public:
    CompositeClass() = default;
    void add(Animal* a);
    PlainStruct get();
private:
    AnimalKingdom mAnimalKingdom;
};

