#include "Matrix.h"

#include <iostream>
#include <algorithm>
#include <exception>

Matrix::Matrix(Dimension d) : mDimension(d), mData(), mRowWritten(), mLastRowWritten(0)
{
   for (size_t i = 0; i < mDimension.m; i++)
   {
      std::vector<int> row{};
      row.resize(mDimension.n);
      std::fill(std::begin(row), std::end(row), 0);
      row.shrink_to_fit();
      mData.push_back(row);
   }

   mData.shrink_to_fit();

   mRowWritten.resize(mDimension.m);
   std::fill(std::begin(mRowWritten), std::end(mRowWritten), false);
}

void Matrix::addRow(std::vector<int> row)
{
   if (row.size() > mDimension.n)
   {
      throw std::length_error("uh oh");
   }
   if (mRowWritten.at(mLastRowWritten) == false)
   {
      mData.at(mLastRowWritten) = row;
      mRowWritten.at(mLastRowWritten) = true;
      mLastRowWritten++;
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

