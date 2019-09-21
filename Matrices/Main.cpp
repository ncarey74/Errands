#include "Matrix.h"

#include <iostream>
#include <string>

int main()
{
   Matrix matrix{Dimension{2, 3}};

   matrix.print();

   std::string name;
   getline(std::cin, name);
   std::cout << "Hello, " << name << "!\n";

   return 0;
}
