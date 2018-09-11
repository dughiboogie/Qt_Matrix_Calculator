#include "vector.h"

/*
 * Costruttore invocato dai costruttori di ColumnVector e RowVector che
 * richiama il costruttore di Matrix.
 */

Vector::Vector(unsigned int rows, unsigned int columns)
    : Matrix(rows, columns) { }

