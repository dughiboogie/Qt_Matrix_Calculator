#include "matrix.h"
#include <iomanip>

/*
 * Costruttore a 2 argomenti; crea un oggetto Matrix di
 * dimensione r e c, e poi setta tutti i valori a 0 tramite il metodo
 * setValue(r, c).
 */

Matrix::Matrix(unsigned int r, unsigned int c) : rows(r), columns(c) {
    values = new double* [rows];
    for(unsigned int i = 0; i < rows; ++i){
        values[i] = new double[columns];
        for(unsigned int j = 0; j < columns; ++j)
            setValue(i, j, 0);
    }
}

/*
 * Costruttore di copia.
 */

Matrix::Matrix(const Matrix &temp) : rows(temp.rows), columns(temp.columns) {
    values = new double* [rows];
    for(unsigned int i = 0; i < rows; ++i){
        values[i] = new double[columns];
        for(unsigned int j = 0; j < columns; ++j)
            setValue(i, j, temp.getValue(i, j));
    }
}

/*
 * Overloading dell'operatore di assegnazione.
 */

Matrix& Matrix::operator=(const Matrix& temp){
    rows = temp.rows;
    columns = temp.columns;
    if(values){
        for(unsigned int i = 0; i < rows; ++i)
            delete [] values[i];
        delete [] values;
    }
    values = new double* [rows];
    for(unsigned int i = 0; i < rows; ++i){
        values[i] = new double[columns];

        for(unsigned int j = 0; j < columns; ++j)
            setValue(i, j, temp.getValue(i, j));
    }
    return *this;
}

/*
 * Distruttore virtuale.
 */

Matrix::~Matrix(){
    if(values){
        for(unsigned int i = 0; i < rows; ++i)
            delete [] values[i];
        delete [] values;
    }
}

/*
 * setValue(i, j, val) setta il valore dell'elemento della matrice di
 * indici (i, j) a val.
 */

void Matrix::setValue(unsigned int i, unsigned int j, double val) {
    if(i > rows || j > columns)
        throw Exception("Size Error");
    values[i][j] = val;
}

/*
 * transpose() ritorna una copia della matrice di invocazione trasposta,
 * ovvero con le righe e le colonne scambiate.
 */

Matrix* Matrix::transpose() const{
    Matrix* temp = new Matrix(columns, rows);
    for(unsigned int i = 0; i < temp->rows; ++i)
        for(unsigned int j = 0; j < temp->columns; ++j)
            temp->setValue(i, j, values[j][i]);
    return temp;
}

/*
 * triangularize() ritorna una copia della matrice di invocazione
 * triangolarizzata, ovvero dove tutti gli elementi (i,j) con j < i
 * sono uguali a 0.
 */

Matrix* Matrix::triangularize() const {
    Matrix* temp = new Matrix(*this);
    unsigned int counter = rows > columns ? columns : rows;

    for(unsigned int j = 0; j < counter; ++j){
        bool firstNull = (temp->values[j][j] == 0);
        for(unsigned int i = j + 1; i < rows; ++i)
            /* se temp.values[i][j] == 0 vai alla prossima riga */
            if(temp->values[i][j] != 0){
                /* se il valore alla prima riga == 0 scambia la prima riga con quella corrente */
                if(firstNull){
                    double* aux = new double[columns];
                    for(unsigned int k = 0; k < columns; ++k)
                        aux[k] = temp->values[i][k];

                    temp->values[i] = temp->values[j];
                    temp->values[j] = aux;
                    delete[] aux;
                    firstNull = false;
                }
                /* se il valore alla prima riga != 0 cambia il valore corrente a 0 */
                else{
                    double coeff = -(temp->values[i][j] / temp->values[j][j]);
                    for(unsigned int k = 0; k < columns; ++k){
                        temp->values[j][k] *= coeff;
                        temp->values[i][k] += temp->values[j][k];
                    }
                }
            }
    }
    return temp;
}

/*
 * Metodo get per il numero di righe della matrice.
 */

unsigned int Matrix::getRows() const { return rows; }

/*
 * Metodo get per il numero di colonne della matrice.
 */

unsigned int Matrix::getColumns() const { return columns; }

/*
 * Metodo get per l'elemento (i, j) della matrice.
 */

double Matrix::getValue(unsigned int i, unsigned int j) const {
    if(i > rows || j > columns)
        throw Exception("Size Error");
    return values[i][j];
}

/*
 * Overloading dell'operatore di uguaglianza fra due matrici.
 */

bool Matrix::operator==(const Matrix& m) const {
    if(rows != m.rows || columns != m.columns)
        return false;
    for(unsigned int i = 0; i < rows; ++i)
        for(unsigned int j = 0; j < columns; ++j)
            if(values[i][j] != m.values[i][j])
                return false;
    return true;
}

/*
 * Overloading dell'operatore di disuguaglianza fra due matrici.
 */

bool Matrix::operator!=(const Matrix& m) const {
    if(rows != m.rows || columns != m.columns)
        return true;
    for(unsigned int i = 0; i < rows; ++i)
        for(unsigned int j = 0; j < columns; ++j)
            if(values[i][j] != m.values[i][j])
                return true;
    return false;
}

/*
 * Ridefinizione dell'operatore di output per una matrice.
 */

std::ostream& operator<<(std::ostream& os, const Matrix& temp){
    os << std::setprecision(2) << std::fixed;
    for(unsigned int i = 0; i < temp.getRows(); ++i){
        for(unsigned int j = 0; j < temp.getColumns(); ++j)
            os << std::setw(8) << temp.getValue(i, j) << ' ';
        os << std::endl;
    }
    return os;
}
