#ifndef COLUMNVECTOR_H
#define COLUMNVECTOR_H
#include "vector.h"

class ColumnVector : public Vector {
public:
    ColumnVector(unsigned int rows);

    void setValue(unsigned int row, double value);
    ColumnVector* triangularize() const;
    Vector* transpose() const;
    double euclideanNorm() const;

    unsigned int getColumns() const;
    double getValue(unsigned int i) const;
};

#endif // COLUMNVECTOR_H
