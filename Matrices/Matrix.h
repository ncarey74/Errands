#pragma once

#include <vector>

struct Dimension
{
   size_t m;
   size_t n;
};

class MatrixRow
{
public:
   MatrixRow(size_t length);
   ~MatrixRow() = default;
   MatrixRow(const MatrixRow&) = default;
   MatrixRow& operator=(const MatrixRow&) = default;

   // Modifiers
   bool fillRow(std::vector<int> row);
   
   // Other member functions
   // none so far

   // Friend functions
   friend std::ostream& operator<<(std::ostream& output, const MatrixRow& matrixRow);
   friend MatrixRow operator+(const MatrixRow& left, const MatrixRow& right);

private:
   std::vector<int> mRowData;
   bool mWritten;

   MatrixRow() = delete;
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
   
   // Modifiers
   void addRow(std::vector<int> row);
   void addRow(MatrixRow row);

   // Other member functions
   // none so far

   // Friend functions
   friend std::ostream& operator<<(std::ostream& output, const Matrix& matrixRow);
   friend Matrix operator+(const Matrix& left, const Matrix& right);

private:
   Dimension mDimension;
   std::vector<MatrixRow> mData;

   Matrix() = delete;
   Matrix(const Matrix&) = delete;
   Matrix& operator=(const Matrix&) = delete;
};
