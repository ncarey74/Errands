#include "GroceryList.h"
#include "GroceryExceptions.h"
#include "Fruit.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace food;

GroceryList::GroceryList() : mList()
{
    std::string fileName{ "D:\\Documents\\Temp Docs\\Fruit.txt" };
    std::ifstream file{ fileName };

    if (file.is_open() == true)
    {
        std::string s{};

        while (getline(file, s))
        {
            AddToList(s);
        }
    }
    else
    {
        throw NoList(fileName);
    }
}

void GroceryList::AddToList(std::string s)
{
    if (s == "apple")
    {
        mList.emplace_back(new Apple{});
    }
    else if (s == "peach")
    {
        mList.emplace_back(new Peach{});
    }
    else if (s == "pear")
    {
        mList.emplace_back(new Pear{});
    }
    else
    {
        throw InvalidItem(s);
    }
}

void GroceryList::read() const
{
    std::cout << "This is my grocery list:" << std::endl;
    for (auto& i : mList)
    {
        std::cout << i->name() << std::endl;
    }
}

void GroceryList::crossItemOffList(const std::string& s)
{
    std::cout << "I don't need this on my list anymore: " << s << std::endl;
    auto findItem = [&s](const GroceryItemPointer& g) { return g->name() == s; };
    mList.erase(std::remove_if(mList.begin(), mList.end(), findItem));
}
