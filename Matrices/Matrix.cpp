#include "Matrix.h"
#include "Exceptions.h"

#include <iostream>
#include <algorithm>
#include <exception>

MatrixRow::MatrixRow(size_t length) : mRowData(), mWritten(false)
{
   mRowData.resize(length);
   std::fill(std::begin(mRowData), std::end(mRowData), 0);
   mRowData.shrink_to_fit();
}

void MatrixRow::print() const
{
   std::cout << "[";
   for (const auto& i : mRowData)
   {
      std::cout << " " << i;
   }
   std::cout << " ]" << std::endl;
}

bool MatrixRow::fillRow(std::vector<int> row)
{
   if (mWritten == false)
   {
      mRowData = row;
      mWritten = true;
      return true;
   }
   return false;
}

Matrix::Matrix(Dimension d) : mDimension(d), mData()
{
   for (size_t i = 0; i < mDimension.m; i++)
   {
      mData.push_back(MatrixRow{ mDimension.n });
   }
   mData.shrink_to_fit();
}

void Matrix::addRow(std::vector<int> row)
{
   if (row.size() > mDimension.n)
   {
      throw TooManyColumns(std::to_string(row.size()));
   }
   
   bool writeSuccess = false;
   for (auto& i : mData)
   {
      if (i.fillRow(row))
      {
         writeSuccess = true;
         break;
      }
   }
   if (!writeSuccess)
   {
      throw TooManyRows(std::to_string(mDimension.m + 1));
   }
}

void Matrix::print() const
{
   std::cout << "The matrix is " << mDimension.m << "x" << mDimension.n << std::endl;
   
   for (const auto& i : mData)
   {
      i.print();
   }
}

