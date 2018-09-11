#ifndef ROWVECTOR_H
#define ROWVECTOR_H
#include "vector.h"

class RowVector : public Vector {
public:
    RowVector(unsigned int columns);

    void setValue(unsigned int column, double value);
    RowVector* triangularize() const;
    Vector* transpose() const;
    double euclideanNorm() const;

    unsigned int getRows() const;
    double getValue(unsigned int j) const;
};

#endif // ROWVECTOR_H
