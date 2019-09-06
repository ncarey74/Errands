#include <iostream>
#include <string>
#include <sstream>
#include <vector>


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

struct Secret
{
   std::string name;
   std::vector<int> data;
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

std::ostream& operator<<(std::ostream& output, const Secret s)
{
   output << "name: " << s.name << "; numbers: ";
   for (auto& i : s.data)
   {
      output << i << ", ";
   }
   output << "; length: " << s.data.size() << std::endl;

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

Secret createAlpha()
{
   Secret s{};
   s.name = "Gundam";

   std::vector<int> v{1, 2, 3};
   s.data = v;

   return s;
}

Secret createBeta()
{
   Secret s{};
   s.name = "Zakue";

   std::vector<int> v{ 4, 5, 6, 7, 8 };
   s.data = v;

   return s;
}

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

   Secret alpha = createAlpha();
   Secret beta = createBeta();

   d.write(alpha);
   d.write(beta);

   char c{};

   std::cin >> c;

   return 0;
}