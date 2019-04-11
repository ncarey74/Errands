#include "CompositeClass.h"

#include <iostream>

void CompositeClass::add(Animal* a) 
{
    mAnimalKingdom.emplace_back(a);
}

/**
* @brief    Returns the composition as a POD struct.
*/
std::unique_ptr<PlainStruct> CompositeClass::get()
{
    //PlainStruct plainStruct{};

    std::unique_ptr<PlainStruct> plainStruct{ new PlainStruct{} };

    plainStruct->alpha = mAnimalKingdom.back().get()->id();
    mAnimalKingdom.pop_back();
    plainStruct->beta = mAnimalKingdom.back().get()->id();

    std::cout << plainStruct->alpha << " " << plainStruct->beta << std::endl;
    
    return plainStruct;
}
