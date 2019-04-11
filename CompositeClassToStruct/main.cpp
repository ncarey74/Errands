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

    PlainStruct p{};

    CompositeClass c{};
    c.add(new Cat{});
    c.add(new Dog{});
    p = c.get();

    char input{};
    std::cin >> input;

    return 0;
}
