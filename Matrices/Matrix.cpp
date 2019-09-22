#include "Matrix.h"
#include "Exceptions.h"

#include <iostream>
#include <algorithm>
#include <exception>


//---------------------------------------------------------------------------------------------------------------------
// Matrix Dimension
//---------------------------------------------------------------------------------------------------------------------

bool operator==(const Dimension& left, const Dimension& right)
{
   return (left.m == right.m) && (left.n == right.n);
}

bool operator!=(const Dimension& left, const Dimension& right)
{
   return !(left == right);
}

void assertMatchingMatrixDimensions(Dimension left, Dimension right)
{
   if (left != right)
   {
      throw std::exception{ "uh oh!" };
   }
}

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

/**
 * @note Assume operation is only performed inside Matrix class, which enforces dimensions
 */
MatrixRow operator+(const MatrixRow& left, const MatrixRow& right)
{
   std::vector<int> summation{};

   std::transform(std::begin(left.mRowData), std::end(left.mRowData), std::begin(right.mRowData), std::back_inserter(summation), std::plus<int>());
   
   MatrixRow result{ left.mRowData.size() };
   result.fillRow(summation);

   return result;
}

/**
* @note Assume operation is only performed inside Matrix class, which enforces dimensions
*/
MatrixRow operator*(int scalar, const MatrixRow& row)
{
   // Why can't I do std::vector<int> scalarValues{ row.mRowData.size(), scalar }; ???
   std::vector<int> scalarValues{};
   scalarValues.resize(row.mRowData.size());
   std::fill(std::begin(scalarValues), std::end(scalarValues), scalar);

   std::vector<int> scalarMultiplication{};

   std::transform(std::begin(row.mRowData), std::end(row.mRowData), std::begin(scalarValues), std::back_inserter(scalarMultiplication), std::multiplies<int>());

   MatrixRow result{ row.mRowData.size() };
   result.fillRow(scalarMultiplication);

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
   assertMatchingMatrixDimensions(left.mDimension, right.mDimension);

   Matrix result{left.mDimension};

   for (size_t i = 0; i < result.mDimension.m; i++)
   {
      result.addRowAt(left.mData.at(i) + right.mData.at(i), i);
   }

   return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
   assertMatchingMatrixDimensions(left.mDimension, right.mDimension);

   Matrix negativeRight = right;
   negativeRight.negate();

   return Matrix{ left + negativeRight };
}

Matrix operator*(int scalar, const Matrix& matrix)
{
   Matrix result{ matrix.mDimension };
   
   for (size_t i = 0; i < result.mDimension.m; i++)
   {
      result.addRowAt(scalar * matrix.mData.at(i), i);
   }

   return result;
}
