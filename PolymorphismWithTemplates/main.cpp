#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>


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

struct ComputerData
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
   output << "name: " << s.name << ", numbers: ";
   for (auto& i : s.data)
   {
      output << i << ", ";
   }
   output << ", length: " << s.data.size() << std::endl;

   return output;
}

std::ostream& operator<<(std::ostream& output, ComputerData c)
{
   output << "name: " << c.name << ", numbers: ";
   for (auto& i : c.data)
   {
      output << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << ", ";
   }
   output << ", length: " << c.data.size() << std::endl;

   return output;
}



//---------------------------------------------------------------------------------------------------------------------
// Data logger classes
//---------------------------------------------------------------------------------------------------------------------

typedef std::string Path;
typedef std::string CommaSeparatedValue;

class CsvFile
{
public:
   CsvFile(Path path) : mPath(path) {}
   void write(CommaSeparatedValue csv)
   {
      std::ofstream file{mPath, std::ios::app};
      if (file.is_open())
      {
         file << csv;
      }
   }
private:
   Path mPath;
};

class DataLogger
{
public:

   template<typename T>
   void write(T data)
   {
      std::ostringstream ss{};
      ss << data;
      mCsvFile.write(ss.str());
   }
private:
   CsvFile mCsvFile{ "D:\\Documents\\Temp Docs\\example.csv" };
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
   s.name = "Zaku";

   std::vector<int> v{ 4, 5, 6, 7, 8 };
   s.data = v;

   return s;
}

ComputerData createGamma()
{
   ComputerData c{};
   c.name = "Zephyr";

   std::vector<int> v{ 256, 257, 432, 7, 22 };
   c.data = v;

   return c;
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
   ComputerData gamma = createGamma();

   d.write(alpha);
   d.write(beta);
   d.write(gamma);

   char c{};

   std::cin >> c;

   return 0;
}