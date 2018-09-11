#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "exception.h"

class Matrix {
private:
    unsigned int rows;
    unsigned int columns;
    double **values;

public:
    Matrix(unsigned int rows, unsigned int columns);
    Matrix(const Matrix& temp);
    Matrix& operator=(const Matrix&);
    virtual ~Matrix();

    void setValue(unsigned int i, unsigned int j, double value);
    virtual Matrix* transpose() const;
    virtual Matrix* triangularize() const;

    virtual unsigned int getRows() const;
    virtual unsigned int getColumns() const;
    double getValue(unsigned int i, unsigned int j) const;

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& temp);

#endif // MATRIX_H
