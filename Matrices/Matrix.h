#pragma once

#include <vector>

struct Dimension
{
   size_t m;
   size_t n;
};

/**
* @note     Uses the compiler's default implementation of the move copy constructor and move assignment operator.
*           A VS2013 bug prevents these two functions from being declared as default.
*/
class Matrix
{
public:
   Matrix(Dimension d);
   ~Matrix() = default;
   
   void addRow(std::vector<int> row);

   void print() const;
private:
   Dimension mDimension;
   std::vector<std::vector<int>> mData;  // Do the obvious implementation for now. Be more efficient later.
   std::vector<bool> mRowWritten;
   size_t mLastRowWritten;

   void printRow(std::vector<int> row) const;

   Matrix() = delete;
   Matrix(const Matrix&) = delete;
   Matrix& operator=(const Matrix&) = delete;
};
