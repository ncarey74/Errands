#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
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
   DataLogger() = default;

   void registerFile(Path path)
   {
      mFiles.emplace(path, path);  // Note that emplace is used, not insert. The key is NOT the same as the value!
   }

   template<typename T>
   void write(Path file, T data)
   {
      std::ostringstream ss{};
      ss << data;
      try
      {
         mFiles.at(file).write(ss.str());
      }
      catch (std::out_of_range e)
      {
         std::cout << "File not registered: " << file << std::endl;
      }
   }
private:
   std::map<Path, CsvFile> mFiles{};
};


//---------------------------------------------------------------------------------------------------------------------
// Main Program
//---------------------------------------------------------------------------------------------------------------------

int main()
{
   std::cout << "Hello world!" << std::endl;

   Path logFile{ "D:\\Documents\\Temp Docs\\example.csv" };
   Path anotherLogFile{ "D:\\Documents\\Temp Docs\\another_file.csv" };
   DataLogger logger{};

   logger.registerFile(logFile);
   logger.registerFile(anotherLogFile);

   logger.write(logFile, Rectangle{ 10, 20 });
   logger.write(logFile, Book{ "Tolkien", "The Silmarillion" });
   logger.write(logFile, Secret{ "Gundam", std::vector<int>{ 1, 2, 3 } });
   logger.write(logFile, Secret{ "Zaku", std::vector<int>{ 4, 5, 6, 7, 8 } });
   logger.write(anotherLogFile, ComputerData{ "Zephyr", std::vector<int>{ 256, 257, 432, 7, 22 } });
   logger.write(anotherLogFile, Book{ "Martin", "A Game of Thrones" });

   char c{};

   std::cin >> c;

   return 0;
}