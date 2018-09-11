#include "squarematrix.h"

/*
 * Costruttore ad un argomento, crea una matrice quadrata r x r.
 */

SquareMatrix::SquareMatrix(unsigned int r) : Matrix(r, r) { }

/*
 * Convertitore da Matrix a SquareMatrix.
 */

SquareMatrix::SquareMatrix(const Matrix & temp) : Matrix(temp) {
    if(temp.getColumns() != temp.getRows())
        throw Exception("Invalid conversion from Matrix to SquareMatrix");
}

/*
 * transpose() ritorna una copia della matrice di invocazione trasposta,
 * ovvero con le righe e le colonne scambiate.
 */

SquareMatrix* SquareMatrix::transpose() const{
    SquareMatrix* temp = new SquareMatrix(getRows());
    for(unsigned int i = 0; i < temp->getRows(); ++i)
        for(unsigned int j = 0; j < temp->getColumns(); ++j)
            temp->setValue(i, j, getValue(j, i));
    return temp;
}

/*
 * triangularize() ritorna una copia della matrice di invocazione
 * triangolarizzata, ovvero dove tutti gli elementi (i,j) con j < i
 * sono uguali a 0.
 */

SquareMatrix* SquareMatrix::triangularize() const{
    return new SquareMatrix(*Matrix::triangularize());
}

/*
 * identityMatrix() ritorna la matrice quadrata identità relativa alla
 * matrice oggetto di invocazione, ovvero una matrice con lo stesso
 * numero di righe e colonne ma con tutti gli elementi uguali a 0, eccetto
 * quelli della diagonale che saranno uguali ad 1.
 */

SquareMatrix* SquareMatrix::identityMatrix() const {
    SquareMatrix* temp = new SquareMatrix(getRows());

    for(unsigned int i = 0; i < getRows(); ++i)
        temp->setValue(i, i, 1);

    return temp;
}

/*
 * determinant() ritorna il determinante della matrice di invocazione.
 */

double SquareMatrix::determinant() const {
    if(getRows() == 2)
        return (getValue(0,0) * getValue(1,1)) - (getValue(0,1) * getValue(1,0));

    if(getRows() == 3)
        return (getValue(0,0) * getValue(1,1) * getValue(2,2)) +
                (getValue(0,1) * getValue(1,2) * getValue(2,0)) +
                (getValue(0,2) * getValue(1,0) * getValue(2,1)) -
                (getValue(2,0) * getValue(1,1) * getValue(0,2)) -
                (getValue(2,1) * getValue(1,2) * getValue(0,0)) -
                (getValue(2,2) * getValue(1,0) * getValue(0,1));

    Matrix* temp = triangularize();
    double det = 1;

    for(unsigned int i = 0; i < getRows(); ++i)
        det *= temp->getValue(i, i);

    delete temp;
    return det;
}

/*
 * inverseMatrix() calcola la matrice inversa della matrice di invocazione
 * (tramite Algoritmo di Gauss - Jordan) e ne ritorna il puntatore.
 */

SquareMatrix* SquareMatrix::inverseMatrix() const {
    if(determinant() == 0)
        throw Exception("Matrix not invertible");

    Matrix* B = new Matrix(getRows(), getColumns() * 2);
    SquareMatrix* result = new SquareMatrix(getRows());
    for(int i = 0; i < getRows(); ++i){
        for(int j = 0; j < getColumns(); ++j)
            B->setValue(i, j, getValue(i, j));
        B->setValue(i, getColumns() + i, 1);
    }
    B = B->triangularize();
    for(int j = getColumns() - 1; j >= 0; --j){
        double pivot = B->getValue(j, j);
        for(int k = j; k < B->getColumns(); ++k)
            B->setValue(j, k, B->getValue(j, k) / pivot);
        for(int i = j - 1; i >= 0; --i){
            if(B->getValue(i, j) != 0){
                double coeff = - B->getValue(i, j);
                for(int k = j; k < B->getColumns(); ++k)
                    B->setValue(i, k, (B->getValue(j, k) * coeff) + B->getValue(i, k));
            }
        }
    }
    for(unsigned int i = 0; i < getRows(); ++i)
        for(unsigned int j = 0; j < getColumns(); ++j)
            result->setValue(i, j, B->getValue(i, j + getColumns()));
    return result;
}
