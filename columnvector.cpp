#include "columnvector.h"
#include "rowvector.h"

/*
 * Costruttore ad un argomento: crea un oggetto ColumnVector di dimensione rows x 1.
 */

ColumnVector::ColumnVector(unsigned int rows) : Vector(rows, 1) { }

/*
 * Il metodo setValue() setta il valore dell'elemento del vettore colonna di invocazione
 * in posizione row a value.
 */

void ColumnVector::setValue(unsigned int row, double value) {
    Matrix::setValue(row, 0, value);
}

/*
 * triangularize() ritorna una copia del vettore di invocazione
 * triangolarizzato, ovvero dove tutti gli elementi (i,j) con j < i
 * sono uguali a 0.
 */

ColumnVector* ColumnVector::triangularize() const{
    ColumnVector* temp = new ColumnVector(getRows());
    Matrix* aux = Matrix::triangularize();
    for(unsigned int i = 0; i < getRows(); ++i)
        temp->setValue(i, aux->getValue(0, i));
    delete aux;
    return temp;
}

/*
 * Il metodo transpose() ritorna il vettore colonna di invocazione trasposto, quindi
 * ritorna un puntatore ad un oggetto di tipo RowVector.
 */

Vector* ColumnVector::transpose() const {
    RowVector* temp = new RowVector(getRows());
    for(unsigned int i = 0; i < getRows(); ++i)
        temp->setValue(i, getValue(i));
    return temp;
}

/*
 * Il metodo euclideanNorm() ritorna la norma del vettore di invocazione.
 */

double  ColumnVector::euclideanNorm() const {
    double result = 0;
    for(unsigned int i = 0; i < getRows(); ++i)
        result += (pow(getValue(i), 2));
    return sqrt(result);
}

/*
 * Metodo get che ritorna il numero di colonne del vettore di invocazione, ovvero
 * ritorna sempre 1.
 */

unsigned int ColumnVector::getColumns() const { return 1; }

/*
 * Metodo get che ritorna il valore dell'elemento del vettore di invocazione in
 * posizione j.
 */

double ColumnVector::getValue(unsigned int i) const {
    return Matrix::getValue(i, 0);
}
