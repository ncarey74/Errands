#include "Matrix.h"
#include "Exceptions.h"

#include <iostream>
#include <algorithm>
#include <exception>


//---------------------------------------------------------------------------------------------------------------------
// Matrix Row
//---------------------------------------------------------------------------------------------------------------------

MatrixRow::MatrixRow(size_t length) : mRowData(), mWritten(false)
{
   mRowData.resize(length);
   std::fill(std::begin(mRowData), std::end(mRowData), 0);
   mRowData.shrink_to_fit();
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

std::ostream& operator<<(std::ostream& output, const MatrixRow& matrixRow)
{
   output << "[";
   for (const auto& i : matrixRow.mRowData)
   {
      output << " " << i;
   }
   output << " ]" << std::endl;

   return output;
}

MatrixRow operator+(const MatrixRow& left, const MatrixRow& right)
{
   // Assume operation is only performed inside Matrix class, which enforces dimensions
   std::vector<int> summation{};
   summation.resize(left.mRowData.size());

   std::transform(std::begin(left.mRowData), std::end(left.mRowData), std::begin(right.mRowData), std::back_inserter(summation), std::plus<int>());
   
   MatrixRow result{ left.mRowData.size() };
   result.fillRow(summation);

   return result;
}


//---------------------------------------------------------------------------------------------------------------------
// Matrix
//---------------------------------------------------------------------------------------------------------------------

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
      throw TooManyColumns{std::to_string(row.size())};
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

void addRow(MatrixRow row)
{
   // how?
}

std::ostream& operator<<(std::ostream& output, const Matrix& matrixRow)
{
   output << "The matrix is " << matrixRow.mDimension.m << "x" << matrixRow.mDimension.n << std::endl;

   for (const auto& i : matrixRow.mData)
   {
      output << i;
   }

   return output;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
   if ((left.mDimension.m != right.mDimension.m) && (left.mDimension.n != right.mDimension.n))
   {
      throw std::exception{ "uh oh!" };
   }

   Matrix result{left.mDimension};

   for (size_t i = 0; i < left.mDimension.m; i++)
   {
      result.addRow(left.mData.at(i) + right.mData.at(i));
   }
}
