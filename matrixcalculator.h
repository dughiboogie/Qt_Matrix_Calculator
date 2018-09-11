#ifndef MATRIXCALCULATOR_H
#define MATRIXCALCULATOR_H
#include "operatorsredefinitions.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

#include "button.h"

class MatrixCalculator : public QWidget {
    Q_OBJECT

public:
    MatrixCalculator(QWidget *parent = 0);

private slots:
    void rectangularClicked();
    void squareClicked();
    void scalarClicked();
    void rowClicked();
    void columnClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void clear();
    void setRows(const QString& value);
    void setColumns(const QString& value);
    void insertValues();
    void setValue(const QString& value);
    void displayMatrix();

private:    
    void abortOperation(const Exception& error);
    Matrix* operand;
    Matrix* matrixSum;
    Matrix* matrixFactor;
    double scalarOperand;
    double tempProduct;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;
    unsigned int rowNumber, columnNumber;
    QTextEdit* display;
};

#endif // MATRIXCALCULATOR_H
