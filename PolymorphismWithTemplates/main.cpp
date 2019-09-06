#include <iostream>
#include <string>
#include <sstream>


//---------------------------------------------------------------------------------------------------------------------
// Data definitions
//---------------------------------------------------------------------------------------------------------------------

struct Rectangle
{
   int width;
   int height;
};

struct Book
{
   std::string author;
   std::string title;
};


//---------------------------------------------------------------------------------------------------------------------
// Output streaming overloads
//---------------------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& output, const Rectangle r)
{
   output << "width: " << r.width << ", height: " << r.height << std::endl;
   return output;
}

std::ostream& operator<<(std::ostream& output, const Book b)
{
   output << "author: " << b.author << ", title: " << b.title << std::endl;
   return output;
}

//---------------------------------------------------------------------------------------------------------------------
// Data logger classes
//---------------------------------------------------------------------------------------------------------------------

class DataLogger
{
public:

   template<typename T>
   void write(T data)
   {
      std::cout << data;
   }
};


//---------------------------------------------------------------------------------------------------------------------
// Main Program
//---------------------------------------------------------------------------------------------------------------------

int main()
{
   std::cout << "Hello world!" << std::endl;

   DataLogger d{};

   Rectangle r{};
   r.height = 10;
   r.width = 20;

   d.write(r);

   Book b{};
   b.author = "Tolkien";
   b.title = "The Silmarillion";

   d.write(b);

   char c{};

   std::cin >> c;

   return 0;
}