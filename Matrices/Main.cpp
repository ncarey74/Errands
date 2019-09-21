#include "Matrix.h"

#include <iostream>
#include <string>

int main()
{
   Matrix matrix{Dimension{2, 3}};

   matrix.print();
   std::cout << std::endl;

   matrix.addRow(std::vector<int>{1, 2, 3});
   matrix.print();
   std::cout << std::endl;

   matrix.addRow(std::vector<int>{4, 5, 6});
   matrix.print();
   std::cout << std::endl;

   std::string name;
   getline(std::cin, name);
   std::cout << "Hello, " << name << "!\n";

   return 0;
}
