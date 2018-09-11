#include "operatorsredefinitions.h"
#include <typeinfo>

/*
 * Ridefinizione dell'operatore di somma per due matrici con la stessa
 * dimensione; se le dimensioni delle due matrici non coincidono viene
 * lanciata un'eccezione. Il tipo di ritorno e' definito dal tipo dinamico
 * del primo operando.
 */

Matrix* operator+(const Matrix& leftOperand, const Matrix& rightOperand) {
    if(leftOperand.getRows() != rightOperand.getRows() || leftOperand.getColumns() != rightOperand.getColumns())
        throw Exception("The two matrices must be of the same size");

    Matrix* result;
    if(leftOperand.getRows() == leftOperand.getColumns())
        result = new SquareMatrix(leftOperand.getRows());
    else {
        if(leftOperand.getRows() == 1)
            result = new RowVector(leftOperand.getColumns());
        else {
            if(leftOperand.getColumns() == 1)
                result = new ColumnVector(leftOperand.getRows());
            else
                result = new Matrix(leftOperand.getRows(), leftOperand.getColumns());
        }
    }

    for(unsigned int i = 0; i < result->getRows(); ++i)
        for(unsigned int j = 0; j < result->getColumns(); ++j)
            result->setValue(i, j, leftOperand.getValue(i, j) + rightOperand.getValue(i, j));

    return result;
}

/*
 * Ridefinizione dell'operatore di differenza per due matrici con la
 * stessa dimensione; se le dimensioni delle due matrici non coincidono
 * viene lanciata un'eccezione. Il tipo di ritorno e' definito dal tipo dinamico
 * del primo operando.
 */

Matrix* operator-(const Matrix& leftOperand, const Matrix& rightOperand) {
    if(leftOperand.getRows() != rightOperand.getRows() || leftOperand.getColumns() != rightOperand.getColumns())
        throw Exception("The two matrices must be of the same size");

    Matrix* result;
    if(leftOperand.getRows() == leftOperand.getColumns())
        result = new SquareMatrix(leftOperand.getRows());
    else {
        if(leftOperand.getRows() == 1)
            result = new RowVector(leftOperand.getColumns());
        else {
            if(leftOperand.getColumns() == 1)
                result = new ColumnVector(leftOperand.getRows());
            else
                result = new Matrix(leftOperand.getRows(), leftOperand.getColumns());
        }
    }

    for(unsigned int i = 0; i < result->getRows(); ++i)
        for(unsigned int j = 0; j < result->getColumns(); ++j)
            result->setValue(i, j, leftOperand.getValue(i, j) - rightOperand.getValue(i, j));

    return result;
}

/*
 *  Ridefinizione dell'operatore di moltiplicazione fra una matrice e uno scalare.
 */

Matrix* operator*(const Matrix& matrix, double scalar) {
    Matrix* result;
    if(matrix.getRows() == matrix.getColumns())
        result = new SquareMatrix(matrix.getRows());
    else {
        if(matrix.getRows() == 1)
            result = new RowVector(matrix.getColumns());
        else {
            if(matrix.getColumns() == 1)
                result = new ColumnVector(matrix.getRows());
            else
                result = new Matrix(matrix.getRows(), matrix.getColumns());
        }
    }

    for(unsigned int i = 0; i < result->getRows(); ++i)
        for(unsigned int j = 0; j < result->getColumns(); ++j)
            result->setValue(i, j, matrix.getValue(i, j) * scalar);

    return result;
}

Matrix* operator*(double scalar, const Matrix& matrix) {
    Matrix* result;
    if(matrix.getRows() == matrix.getColumns())
        result = new SquareMatrix(matrix.getRows());
    else {
        if(matrix.getRows() == 1)
            result = new RowVector(matrix.getColumns());
        else {
            if(matrix.getColumns() == 1)
                result = new ColumnVector(matrix.getRows());
            else
                result = new Matrix(matrix.getRows(), matrix.getColumns());
        }
    }

    for(unsigned int i = 0; i < result->getRows(); ++i)
        for(unsigned int j = 0; j < result->getColumns(); ++j)
            result->setValue(i, j, matrix.getValue(i, j) * scalar);

    return result;
}

/*
 * Ridefinizione del prodotto fra due matrici; se il numero di colonne
 * della prima matrice non coincide con il numero delle righe della
 * seconda viene lanciata un'eccezione. Il tipo di ritorno è determinato
 * dal numero di colonnee di righe della matrice risultato.
 */

Matrix* operator*(const Matrix& leftOperand, const Matrix& rightOperand) {
    if(leftOperand.getColumns() != rightOperand.getRows())
        throw Exception("The number of columns of the first matrix must be the same as the numbero of rows of the second matrix");

    Matrix* result;
    if(leftOperand.getRows() == rightOperand.getColumns())
        result = new SquareMatrix(leftOperand.getRows());
    else {
        if(leftOperand.getRows() == 1)
            result = new RowVector(rightOperand.getColumns());
        else {
            if(rightOperand.getColumns() == 1)
                result = new ColumnVector(leftOperand.getRows());
            else
                result = new Matrix(leftOperand.getRows(), rightOperand.getColumns());
        }
    }

    for(unsigned int i = 0; i < result->getRows(); ++i)
        for(unsigned int j = 0; j < result->getColumns(); ++j){
            double t = 0;
            for(unsigned int k = 0; k < leftOperand.getColumns(); ++k)
                t += (leftOperand.getValue(i, k) * rightOperand.getValue(k, j));

            result->setValue(i, j, t);
        }

    return result;
}
