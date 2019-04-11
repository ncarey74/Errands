#include <iostream>

#include "PlainStruct.h"
#include "CompositeClass.h"

/**
*   @brief  Main function in experiment to see how practical it is to have a composite object using OO translate to
*           a POD struct.
*/
int main()
{
    std::cout << "hello world" << std::endl;

    CompositeClass c{};
    c.add(new Cat{});
    c.add(new Dog{});
    auto returnedUniquePointer = c.get();

    PlainStruct p = *returnedUniquePointer;

    std::cout << "I got " << p.alpha << " and " << p.beta << std::endl;

    char input{};
    std::cin >> input;

    return 0;
}
