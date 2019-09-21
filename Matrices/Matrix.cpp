#include "Matrix.h"

#include <iostream>

Matrix::Matrix(Dimension d) : mDimension(d), mData()
{
   mData.reserve(mDimension.m);
   mData.shrink_to_fit();

   for (size_t i = 0; i < mDimension.m; i++)
   {
      std::vector<int> row{};
      //row.reserve(mDimension.n);
      //row.shrink_to_fit();
      //std::fill(std::begin(row), std::end(row), 0);
      //mData.push_back(row);
      for (size_t j = 0; j < mDimension.n; j++)
      {
         row.push_back(0);
      }
      mData.push_back(row);
   }
}

void Matrix::print() const
{
   for (const auto& i : mData)
   {
      printRow(i);
   }
}

void Matrix::printRow(std::vector<int> row) const
{
   std::cout << "[";
   for (const auto& i : row)
   {
      std::cout << " " << i;
   }
   std::cout << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& output, Matrix& matrix)
{
   
   return output;
}
