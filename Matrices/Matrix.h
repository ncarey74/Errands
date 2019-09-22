#pragma once

#include <vector>

struct Dimension
{
   size_t m;
   size_t n;
};

bool operator==(const Dimension& left, const Dimension& right);
bool operator!=(const Dimension& left, const Dimension& right);

void assertMatchingMatrixDimensions(Dimension left, Dimension right);

class MatrixRow
{
public:
   explicit MatrixRow(size_t length);
   ~MatrixRow() = default;
   MatrixRow(const MatrixRow&) = default;
   MatrixRow& operator=(const MatrixRow&) = default;

   // Modifiers
   bool fillRow(std::vector<int> row);
   void negate();
   
   // Other member functions
   // none so far

   // Friend functions
   friend std::ostream& operator<<(std::ostream& output, const MatrixRow& matrixRow);
   friend MatrixRow operator+(const MatrixRow& left, const MatrixRow& right);
   friend MatrixRow operator-(const MatrixRow& left, const MatrixRow& right);
   friend MatrixRow operator*(int scalar, const MatrixRow& matrix);

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
   explicit Matrix(Dimension d);
   ~Matrix() = default;
   Matrix(const Matrix&) = default;
   Matrix& operator=(const Matrix&) = default;
   Matrix(Matrix&& other);  // VS2013 doesn't allow for implict move constructor, nor can it be defaulted. Must define.
   Matrix& operator=(Matrix&& other);  // VS2013 doesn't allow for implict move assignment, nor can it be defaulted. Must define.
   
   // Modifiers
   void addRow(std::vector<int> row);
   void negate();

   // Other member functions
   // none so far

   // Friend functions
   friend std::ostream& operator<<(std::ostream& output, const Matrix& matrixRow);
   friend Matrix operator+(const Matrix& left, const Matrix& right);
   friend Matrix operator-(const Matrix& left, const Matrix& right);
   friend Matrix operator*(int scalar, const Matrix& matrix);

private:
   Dimension mDimension;
   std::vector<MatrixRow> mData;

   // Modifiers
   void addRowAt(MatrixRow row, size_t index);

   Matrix() = delete;
};
