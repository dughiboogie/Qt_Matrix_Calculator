#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include "matrix.h"

class SquareMatrix : public Matrix {
public:
    SquareMatrix(unsigned int rows);
    SquareMatrix(const Matrix&);

    SquareMatrix* transpose() const;
    SquareMatrix* triangularize() const;
    SquareMatrix* identityMatrix() const;
    double determinant() const;
    SquareMatrix* inverseMatrix() const;
};

#endif // SQUAREMATRIX_H
