#ifndef OPERATORSREDEFINITIONS_H
#define OPERATORSREDEFINITIONS_H
#include "squarematrix.h"
#include "rowvector.h"
#include "columnvector.h"

Matrix* operator+(const Matrix& leftOperand, const Matrix& rightOperand);
Matrix* operator-(const Matrix& leftOperand, const Matrix& rightOperand);
Matrix* operator*(const Matrix& matrix, double scalar);
Matrix* operator*(double scalar, const Matrix& matrix);
Matrix* operator*(const Matrix& leftOperand, const Matrix& rightOperand);

#endif // OPERATORSREDEFINITIONS_H
