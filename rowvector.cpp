#include "rowvector.h"
#include "columnvector.h"

/*
 * Costruttore ad un argomento: crea un oggetto RowVector di dimensione 1 x columns.
 */

RowVector::RowVector(unsigned int columns) : Vector(1, columns) { }

/*
 * Il metodo setValue() setta il valore dell'elemento del vettore riga di invocazione
 * in posizione column a value.
 */

void RowVector::setValue(unsigned int column, double value) {
    Matrix::setValue(0, column, value);
}

/*
 * triangularize() ritorna una copia del vettore di invocazione
 * triangolarizzato, ovvero dove tutti gli elementi (i,j) con j < i
 * sono uguali a 0.
 */

RowVector* RowVector::triangularize() const{
    RowVector* temp = new RowVector(getColumns());
    Matrix* aux = Matrix::triangularize();
    for(unsigned int i = 0; i < getColumns(); ++i)
        temp->setValue(i, aux->getValue(0, i));
    delete aux;
    return temp;
}

/*
 * Il metodo transpose() ritorna il vettore riga di invocazione trasposto, quindi
 * ritorna un puntatore ad un oggetto di tipo ColumnVector.
 */

Vector* RowVector::transpose() const {
    ColumnVector* temp = new ColumnVector(getColumns());
    for(unsigned int j = 0; j < getColumns(); ++j)
        temp->setValue(j, getValue(j));
    return temp;
}

/*
 * Il metodo euclideanNorm() ritorna la norma del vettore di invocazione.
 */

double RowVector::euclideanNorm() const {
    double result = 0;
    for(unsigned int j = 0; j < getColumns(); ++j)
        result += (pow(getValue(j), 2));
    return sqrt(result);
}

/*
 * Metodo get che ritorna il numero di righe del vettore di invocazione, ovvero
 * ritorna sempre 1.
 */

unsigned int RowVector::getRows() const { return 1; }

/*
 * Metodo get che ritorna il valore dell'elemento del vettore di invocazione in
 * posizione j.
 */

double RowVector::getValue(unsigned int j) const {
    return Matrix::getValue(0, j);
}
