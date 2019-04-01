#include <vector>
#include <memory>
#include <iostream>
#include <string>

class GroceryItem
{
public:
    virtual std::string name() = 0;
};

class Fruit : public GroceryItem
{
public:
    virtual std::string name() = 0;
};

class Apple : public Fruit
{
public:
    std::string name()
    {
        return mName;
    }
private:
    std::string mName = "apple";
};

typedef std::unique_ptr<GroceryItem> SmartPointer;
typedef std::vector<SmartPointer> SmartPointerVector;

class GroceryList
{
public:
    GroceryList() : myVector()
    {
        myVector.emplace_back(new Apple());
        myVector.emplace_back(new Apple());

        for (auto& i : myVector)
        {
            std::cout << i->name() << std::endl;
        }
        char c{};
        std::cin >> c;
    }
private:
    SmartPointerVector myVector;
};

void main()
{
    GroceryList{};

}