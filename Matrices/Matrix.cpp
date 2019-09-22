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

void MatrixRow::negate()
{
   for (auto& i : mRowData)
   {
      i = -i;
   }
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

Matrix::Matrix(Matrix&& other) : mDimension(other.mDimension), mData(other.mData)
{
   other.mDimension = Dimension{0, 0};
   other.mData.clear();
}

Matrix& Matrix::operator=(Matrix&& other)
{
   if (this != &other)
   {
      mDimension = other.mDimension;
      mData = other.mData;

      other.mDimension = Dimension{ 0, 0 };
      other.mData.clear();
   }
   return *this;
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

void Matrix::addRowAt(MatrixRow row, size_t index)
{
   mData.at(index) = row;
}

void Matrix::negate()
{
   for (auto& i : mData)
   {
      i.negate();
   }
}

std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
{
   output << "The matrix is " << matrix.mDimension.m << "x" << matrix.mDimension.n << std::endl;

   for (const auto& i : matrix.mData)
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
      result.addRowAt(left.mData.at(i) + right.mData.at(i), i);
   }

   return result;
}
