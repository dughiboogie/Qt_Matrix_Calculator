#include "matrixcalculator.h"
#include <QApplication>

#include "squarematrix.h"
#include "columnvector.h"
#include "rowvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MatrixCalculator w;
    w.show();
    return a.exec();
}
