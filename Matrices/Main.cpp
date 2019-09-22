#include "Matrix.h"

#include <iostream>
#include <string>

int main()
{
   Matrix a{Dimension{2, 3}};

   a.addRow(std::vector<int>{1, 2, 3});
   a.addRow(std::vector<int>{4, 5, 6});
   std::cout << a << std::endl;

   Matrix b{ Dimension{ 2, 3 } };

   b.addRow(std::vector<int>{10, 20, 30});
   b.addRow(std::vector<int>{40, 50, 60});
   std::cout << b << std::endl;

   Matrix c = a + b;
   std::cout << c << std::endl;

   std::string name;
   getline(std::cin, name);
   std::cout << "Hello, " << name << "!\n";

   return 0;
}
