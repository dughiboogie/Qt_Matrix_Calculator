#ifndef VECTOR_H
#define VECTOR_H
#include "matrix.h"
#include <cmath>

class Vector : public Matrix {
public:
    Vector(unsigned int rows, unsigned int columns);
    virtual double euclideanNorm() const = 0;
};

#endif // VECTOR_H
