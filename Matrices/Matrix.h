#pragma once

#include <vector>

struct Dimension
{
   size_t m;
   size_t n;
};

class Matrix
{
public:
   Matrix(Dimension d);
   
   void print() const;
private:
   Dimension mDimension;
   std::vector<std::vector<int>> mData;  // Do the obvious implementation for now. Be more efficient later.

   void printRow(std::vector<int> row) const;

   Matrix() = delete;
};

std::ostream& operator<<(std::ostream& output, Matrix& month);