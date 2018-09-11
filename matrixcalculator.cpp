#include "matrixcalculator.h"

/*
 * Costruttore ad un argomento: crea un oggetto MatrixCalculator con padre parent.
 */

MatrixCalculator::MatrixCalculator(QWidget* parent)
    : QWidget(parent), operand(0), matrixSum(0), matrixFactor(0), scalarOperand(0.0),
      tempProduct(0), waitingForOperand(true), rowNumber(0), columnNumber(0) {
    QGridLayout* mainLayout = new QGridLayout;
    setFixedSize(400, 550);
    setWindowTitle("Matrix Calculator");

    display = new QTextEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->append("");
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 3);
    display->setFont(font);
    mainLayout->addWidget(display, 0, 0, 1, 6);

    Button* rectangular = new Button("n x m", this);
    connect(rectangular, SIGNAL(clicked()), this, SLOT(rectangularClicked()));
    mainLayout->addWidget(rectangular, 2, 0, 1, 2);

    Button* square = new Button("n x n", this);
    connect(square, SIGNAL(clicked()), this, SLOT(squareClicked()));
    mainLayout->addWidget(square, 2, 2, 1, 2);

    Button* row = new Button("1 x n", this);
    connect(row, SIGNAL(clicked()), this, SLOT(rowClicked()));
    mainLayout->addWidget(row, 3, 0, 1, 2);

    Button* column = new Button("n x 1", this);
    connect(column, SIGNAL(clicked()), this, SLOT(columnClicked()));
    mainLayout->addWidget(column, 3, 2, 1, 2);

    Button* scalar = new Button("SCALAR", this);
    connect(scalar, SIGNAL(clicked()), this, SLOT(scalarClicked()));
    mainLayout->addWidget(scalar, 4, 1, 1, 2);

    Button* plus = new Button("+", this);
    connect(plus, SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    mainLayout->addWidget(plus, 2, 5, 1, 1);

    Button* minus = new Button("-", this);
    connect(minus, SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    mainLayout->addWidget(minus, 3, 5, 1, 1);

    Button* product = new Button("x", this);
    connect(product, SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
    mainLayout->addWidget(product, 4, 5, 1, 1);

    Button* equals = new Button("=", this);
    connect(equals, SIGNAL(clicked()), this, SLOT(equalClicked()));
    mainLayout->addWidget(equals, 5, 5, 1, 1);

    Button* clearButton = new Button("C", this);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    mainLayout->addWidget(clearButton, 6, 5, 1, 1);

    Button* transpose = new Button("Transpose", this);
    connect(transpose, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(transpose, 5, 0, 1, 2);

    Button* triangularize = new Button("Triangularize", this);
    connect(triangularize, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(triangularize, 5, 2, 1, 2);

    Button* identity = new Button("Identity Matrix", this);
    connect(identity, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(identity, 6, 0, 1, 2);

    Button* determinant = new Button("Determinant", this);
    connect(determinant, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(determinant, 6, 2, 1, 2);

    Button* inverse = new Button("Inverse Matrix", this);
    connect(inverse, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(inverse, 7, 0, 1, 2);

    Button* euclidean = new Button("Euclidean Norm", this);
    connect(euclidean, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    mainLayout->addWidget(euclidean, 7, 2, 1, 2);

    mainLayout->setColumnMinimumWidth(0, 79);
    mainLayout->setColumnMinimumWidth(1, 79);
    mainLayout->setColumnMinimumWidth(2, 79);
    mainLayout->setColumnMinimumWidth(3, 79);
    mainLayout->setColumnMinimumWidth(4, 5);
    mainLayout->setColumnMinimumWidth(5, 79);
    mainLayout->setRowMinimumHeight(1, 10);
    setLayout(mainLayout);
}

/*
 * Il metodo rectangularClicked() crea una nuova finestra con due QLineEdit in cui
 * andranno digitate le dimensioni della matrice n x m che si vuole creare.
 */

void MatrixCalculator::rectangularClicked() {
    QMessageBox* dimensionsWindow = new QMessageBox;
    QGridLayout* dimensionsLayout = new QGridLayout;
    dimensionsWindow->setWindowTitle("n x m MATRIX");

    QLineEdit* rowsEdit = new QLineEdit(dimensionsWindow);
    rowsEdit->setFixedSize(40, 20);
    rowsEdit->setAlignment(Qt::AlignRight);
    rowsEdit->setInputMask("D0");
    dimensionsLayout->addWidget(new QLabel("Rows:", dimensionsWindow), 1, 1, 1, 1);
    dimensionsLayout->addWidget(rowsEdit, 3, 1, 1, 1);
    connect(rowsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setRows(const QString&)));
    connect(rowsEdit, SIGNAL(returnPressed()), dimensionsWindow, SLOT(close()));
    connect(rowsEdit, SIGNAL(returnPressed()), this, SLOT(insertValues()));

    QLineEdit* columnsEdit = new QLineEdit(dimensionsWindow);
    columnsEdit->setFixedSize(40, 20);
    columnsEdit->setAlignment(Qt::AlignRight);
    columnsEdit->setInputMask("D0");
    dimensionsLayout->addWidget(new QLabel("Columns:", dimensionsWindow), 1, 3, 1, 1);
    dimensionsLayout->addWidget(columnsEdit, 3, 3, 1, 1);
    connect(columnsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setColumns(const QString&)));
    connect(columnsEdit, SIGNAL(returnPressed()), dimensionsWindow, SLOT(close()));
    connect(columnsEdit, SIGNAL(returnPressed()), this, SLOT(insertValues()));

    Button* next = new Button("Next", dimensionsWindow);
    dimensionsLayout->addWidget(next, 5, 2, 1, 1);
    connect(next, SIGNAL(clicked()), dimensionsWindow, SLOT(close()));
    connect(next, SIGNAL(clicked()), this, SLOT(insertValues()));

    delete dimensionsWindow->layout();
    dimensionsWindow->setLayout(dimensionsLayout);
    dimensionsWindow->show();
}

/*
 * Il metodo squareClicked() crea una nuova finestra con un QLineEdit in cui
 * andra' digitata le dimensione della matrice n x n che si vuole creare.
 */

void MatrixCalculator::squareClicked() {
    QMessageBox* dimensionsWindow = new QMessageBox;
    QGridLayout* dimensionsLayout = new QGridLayout;
    dimensionsWindow->setWindowTitle("n x n SQUARE MATRIX");

    QLineEdit* dimensionsEdit = new QLineEdit(dimensionsWindow);
    dimensionsEdit->setFixedSize(40, 20);
    dimensionsEdit->setAlignment(Qt::AlignRight);
    dimensionsEdit->setInputMask("D0");
    dimensionsLayout->addWidget(new QLabel("Rows/Columns:", dimensionsWindow), 1, 2, 1, 3);
    dimensionsLayout->addWidget(dimensionsEdit, 3, 2, 1, 1);
    dimensionsLayout->setColumnMinimumWidth(1, 20);
    dimensionsLayout->setColumnMinimumWidth(3, 20);
    connect(dimensionsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setRows(const QString&)));
    connect(dimensionsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setColumns(const QString&)));
    connect(dimensionsEdit, SIGNAL(returnPressed()), dimensionsWindow, SLOT(close()));
    connect(dimensionsEdit, SIGNAL(returnPressed()), this, SLOT(insertValues()));

    Button* next = new Button("Next", dimensionsWindow);
    dimensionsLayout->addWidget(next, 5, 2, 1, 1);
    connect(next, SIGNAL(clicked()), dimensionsWindow, SLOT(close()));
    connect(next, SIGNAL(clicked()), this, SLOT(insertValues()));

    delete dimensionsWindow->layout();
    dimensionsWindow->setLayout(dimensionsLayout);
    dimensionsWindow->show();
}

/*
 * Il metodo scalarClicked() crea una nuova finestra con un QLineEdit in cui
 * andra' digitato il valore dello scalare che si vuole inserire.
 */

void MatrixCalculator::scalarClicked() {
    rowNumber = 1;
    columnNumber = 1;
    insertValues();
}

/*
 * Il metodo rowClicked() crea una nuova finestra con un QLineEdit in cui
 * andra' digitata le dimensione del vettore riga 1 x n che si vuole creare.
 */

void MatrixCalculator::rowClicked() {
    QMessageBox* dimensionsWindow = new QMessageBox;
    QGridLayout* dimensionsLayout = new QGridLayout;
    dimensionsWindow->setWindowTitle("1 x n ROW VECTOR");
    rowNumber = 1;

    QLineEdit* dimensionsEdit = new QLineEdit(dimensionsWindow);
    dimensionsEdit->setFixedSize(40, 20);
    dimensionsEdit->setAlignment(Qt::AlignRight);
    dimensionsEdit->setInputMask("D0");
    dimensionsLayout->addWidget(new QLabel("Columns:", dimensionsWindow), 1, 2, 1, 3);
    dimensionsLayout->addWidget(dimensionsEdit, 3, 2, 1, 1);
    connect(dimensionsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setColumns(const QString&)));
    connect(dimensionsEdit, SIGNAL(returnPressed()), dimensionsWindow, SLOT(close()));
    connect(dimensionsEdit, SIGNAL(returnPressed()), this, SLOT(insertValues()));

    Button* next = new Button("Next", dimensionsWindow);
    dimensionsLayout->addWidget(next, 5, 2, 1, 1);
    connect(next, SIGNAL(clicked()), dimensionsWindow, SLOT(close()));
    connect(next, SIGNAL(clicked()), this, SLOT(insertValues()));

    dimensionsLayout->setColumnMinimumWidth(1, 20);
    dimensionsLayout->setColumnMinimumWidth(3, 20);

    delete dimensionsWindow->layout();
    dimensionsWindow->setLayout(dimensionsLayout);
    dimensionsWindow->show();
}

/*
 * Il metodo columnClicked() crea una nuova finestra con un QLineEdit in cui
 * andra' digitata le dimensione del vettore colonna n x 1 che si vuole creare.
 */

void MatrixCalculator::columnClicked() {
    QMessageBox* dimensionsWindow = new QMessageBox;
    QGridLayout* dimensionsLayout = new QGridLayout;
    dimensionsWindow->setWindowTitle("n x 1 COLUMN VECTOR");
    columnNumber = 1;

    QLineEdit* dimensionsEdit = new QLineEdit(dimensionsWindow);
    dimensionsEdit->setFixedSize(40, 20);
    dimensionsEdit->setAlignment(Qt::AlignRight);
    dimensionsEdit->setInputMask("D0");
    dimensionsLayout->addWidget(new QLabel("Rows:", dimensionsWindow), 1, 2, 1, 3);
    dimensionsLayout->addWidget(dimensionsEdit, 3, 2, 1, 1);
    dimensionsLayout->setColumnMinimumWidth(1, 20);
    dimensionsLayout->setColumnMinimumWidth(3, 20);
    connect(dimensionsEdit, SIGNAL(textEdited(const QString&)), this, SLOT(setRows(const QString&)));
    connect(dimensionsEdit, SIGNAL(returnPressed()), dimensionsWindow, SLOT(close()));
    connect(dimensionsEdit, SIGNAL(returnPressed()), this, SLOT(insertValues()));

    Button* next = new Button("Next", dimensionsWindow);
    dimensionsLayout->addWidget(next, 5, 2, 1, 1);
    connect(next, SIGNAL(clicked()), dimensionsWindow, SLOT(close()));
    connect(next, SIGNAL(clicked()), this, SLOT(insertValues()));

    delete dimensionsWindow->layout();
    dimensionsWindow->setLayout(dimensionsLayout);
    dimensionsWindow->show();
}

/*
 * Il metodo unaryOperatorClicked() esegue l'operazione cliccata sull'ultima matrice inserita.
 * Se l'ultimo pulsante cliccato è stato un operatore o non è presente una matrice non
 * succede nulla.
 * Inoltre, se si cerca di invocare questo metodo su uno scalare, si ricevera' un messaggio di
 * errore con conseguente perdita dei dati immessi fino a quel momento.
 * Una volta eseguita l'operazione visualizza sul display il risultato.
 */

void MatrixCalculator::unaryOperatorClicked() {
    if(waitingForOperand)
        return;

    if(scalarOperand != 0.0 || (tempProduct != 0.0 && pendingMultiplicativeOperator.isEmpty()))
        abortOperation(Exception("Cannot do such operation with a scalar"));

    Button* buttonClicked = qobject_cast<Button*>(sender());
    QString operation = buttonClicked->text();

    if(operand){
        Matrix* tempOperand = operand;
        try{
            if(operation == "Transpose")
                operand = tempOperand->transpose();

            if(operation == "Triangularize")
                operand = tempOperand->triangularize();

            /* JUST SQUARE MATRICES */

            if(operation == "Identity Matrix"){
                if(!dynamic_cast<SquareMatrix*>(tempOperand))
                    throw(Exception("Operation possible only with square matrices"));
                operand = (static_cast<SquareMatrix*>(tempOperand))->identityMatrix();
            }

            if(operation == "Determinant"){
                if(!dynamic_cast<SquareMatrix*>(tempOperand))
                    throw(Exception("Operation possible only with square matrices"));
                scalarOperand = (static_cast<SquareMatrix*>(tempOperand))->determinant();
                operand = 0;
            }

            if(operation == "Inverse Matrix"){
                if(!dynamic_cast<SquareMatrix*>(tempOperand))
                    throw(Exception("Operation possible only with square matrices"));
                operand = (static_cast<SquareMatrix*>(tempOperand))->inverseMatrix();
            }

            /* JUST VECTORS */

            if(operation == "Euclidean Norm"){
                if(!dynamic_cast<Vector*>(tempOperand))
                    throw(Exception("Operation possible only with vectors"));
                scalarOperand = (static_cast<Vector*>(tempOperand))->euclideanNorm();
                operand = 0;
            }

            delete tempOperand;
        }
        catch(const Exception& error){
            abortOperation(error);
        }

    }
    displayMatrix();
}

/*
 * Il metodo additiveOperatorClicked() aggiunge l'operatore cliccato sul display.
 * Se sono presenti operazioni da risolvere ed e' possibile risolverle (per questioni
 * di priorita') allora vengono risolte, e la matrice risultato e' visualizzata prima
 * dell'operatore appena cliccato.
 * Inoltre, se si tenta di invocare un operatore di questo tipo su uno scalare si
 * ricevera' un messaggio di errore, con conseguente perdita dei dati immessi fino a
 * quel momento.
 */

void MatrixCalculator::additiveOperatorClicked() {
    /* Caso in cui non ci sia una matrice o sia gia' stato cliccato un operatore
     * appena prima di questo */
    if(waitingForOperand){
        if(!pendingAdditiveOperator.isEmpty())
            return;
        if(!pendingMultiplicativeOperator.isEmpty()){
            if(tempProduct != 0.0)
                abortOperation(Exception("Cannot add a scalar to a matrix"));
            if(matrixFactor){
                operand = matrixFactor;
                matrixFactor = 0;
                waitingForOperand = false;
                pendingMultiplicativeOperator.clear();
                additiveOperatorClicked();
                return;
            }
        }
        return;
    }

    /* Caso in cui si tenti di invocare l'operatore su uno scalare */
    if((scalarOperand != 0.0 || tempProduct != 0.0) && !operand && !matrixFactor)
        abortOperation(Exception("Cannot add a scalar to a matrix"));

    /* Risoluzione dell'eventuale operatore di moltiplicazione */
    if(!pendingMultiplicativeOperator.isEmpty()){
        if(operand){
            Matrix* tempOperand = operand;
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                try{
                    matrixFactor = *tempFactor * *tempOperand;
                }
                catch(const Exception& error){
                    abortOperation(error);
                    return;
                }
                delete tempFactor;
            }
            else if(tempProduct != 0.0){
                matrixFactor = *tempOperand * tempProduct;
                tempProduct = 0.0;
            }
            operand = 0;
            delete tempOperand;
        }
        if(scalarOperand != 0.0){
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                matrixFactor = *tempFactor * scalarOperand;
                delete tempFactor;
            }
            if(tempProduct != 0.0)
                tempProduct *= scalarOperand;
            scalarOperand = 0.0;
        }
        pendingMultiplicativeOperator.clear();
    }

    /* Risoluzione dell'eventuale operatore di addizione/sottrazione */
    if(!pendingAdditiveOperator.isEmpty()){
        Matrix* tempSum = matrixSum;
        if(operand){
            Matrix* tempOperand = operand;
            operand = 0;
            try{
                if(pendingAdditiveOperator == "+")
                    matrixSum = *tempSum + *tempOperand;
                if(pendingAdditiveOperator == "-")
                    matrixSum = *tempSum - *tempOperand;
            }
            catch(const Exception& error){
                abortOperation(error);
                return;
            }
            delete tempOperand;
        }
        else if(matrixFactor){
            Matrix* tempFactor = matrixFactor;
            matrixFactor = 0;
            try{
                if(pendingAdditiveOperator == "+")
                    matrixSum = *tempSum + *tempFactor;
                if(pendingAdditiveOperator == "-")
                    matrixSum = *tempSum - *tempFactor;
            }
            catch(const Exception& error){
                abortOperation(error);
                return;
            }
            delete tempFactor;
        }
        delete tempSum;
    }

    /* Caso in cui non siano stati inseriti operatori prima di questo */
    if(operand){
        matrixSum = operand;
        operand = 0;
    }

    /* Caso in cui sia stata eseguita una moltiplicazione prima dell'inserimento
     * di questo operatore */
    if(matrixFactor){
        matrixSum = matrixFactor;
        matrixFactor = 0;
    }

    Button* clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text();
    pendingAdditiveOperator = clickedOperator;
    displayMatrix();
}

/*
 * Il metodo additiveOperatorClicked() aggiunge l'operatore cliccato sul display.
 * Se sono presenti operazioni da risolvere ed e' possibile risolverle (per questioni
 * di priorita') allora vengono risolte, e la matrice risultato e' visualizzata prima
 * dell'operatore appena cliccato.
 */

void MatrixCalculator::multiplicativeOperatorClicked(){
    /* Caso in cui non ci sia una matrice/scalare o sia gia' stato premuto un operatore
     * appena prima di questo */
    if(waitingForOperand){
        if(!pendingMultiplicativeOperator.isEmpty())
            return;
        if(!pendingAdditiveOperator.isEmpty()){
            operand = matrixSum;
            matrixSum = 0;
            waitingForOperand = false;
            pendingAdditiveOperator.clear();
            multiplicativeOperatorClicked();
            return;
        }
        return;
    }

    /*  Risoluzione dell'eventuale operatore di moltiplicazione */
    if(!pendingMultiplicativeOperator.isEmpty()){
        if(operand){
            Matrix* tempOperand = operand;
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                try{
                    matrixFactor = *tempFactor * *tempOperand;
                }
                catch(const Exception& error){
                    abortOperation(error);
                    return;
                }
                delete tempFactor;
            }
            else if(tempProduct != 0.0){
                matrixFactor = *tempOperand * tempProduct;
                tempProduct = 0.0;
            }
            operand = 0;
            delete tempOperand;
        }
        if(scalarOperand != 0.0){
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                matrixFactor = *tempFactor * scalarOperand;
                delete tempFactor;
            }
            if(tempProduct != 0.0)
                tempProduct *= scalarOperand;
            scalarOperand = 0.0;
        }
    }

    /* Caso in cui non siano stati inseriti operatori prima di questo */
    if(operand){
        matrixFactor = operand;
        operand = 0;
    }

    /* Caso in cui sia stata eseguita una moltiplicazione prima dell'inserimento
     * di questo operatore */
    if(scalarOperand){
        tempProduct = scalarOperand;
        scalarOperand = 0.0;
    }

    pendingMultiplicativeOperator = "x";
    displayMatrix();
}

/*
 * Il metodo equalClicked() risolve tutti gli operatori visualizzati sul display, e
 * visualizza il risultato finale.
 */

void MatrixCalculator::equalClicked(){
    /* Caso in cui non ci sia una matrice o sia stato premuto un operatore appena
     * prima di questo metodo */
    if(waitingForOperand){
        if(!pendingMultiplicativeOperator.isEmpty()){
            if(matrixFactor){
                operand = matrixFactor;
                matrixFactor = 0;
            }
            if(tempProduct){
                scalarOperand = tempProduct;
                tempProduct = 0.0;
            }
            pendingMultiplicativeOperator.clear();
            waitingForOperand = false;
            equalClicked();
            return;
        }

        if(!pendingAdditiveOperator.isEmpty()){
            pendingAdditiveOperator.clear();
            waitingForOperand = false;
            equalClicked();
            return;
        }
        return;
    }

    /*  Risoluzione dell'eventuale operatore di moltiplicazione */
    if(!pendingMultiplicativeOperator.isEmpty()){
        if(operand){
            Matrix* tempOperand = operand;
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                try{
                    matrixFactor = *tempFactor * *tempOperand;
                }
                catch(const Exception& error){
                    abortOperation(error);
                    return;
                }
                delete tempFactor;
            }
            else if(tempProduct != 0.0){
                matrixFactor = *tempOperand * tempProduct;
                tempProduct = 0.0;
            }
            operand = 0;
            delete tempOperand;
        }
        if(scalarOperand != 0.0){
            if(matrixFactor){
                Matrix* tempFactor = matrixFactor;
                matrixFactor = *tempFactor * scalarOperand;
                delete tempFactor;
            }
            if(tempProduct != 0.0)
                tempProduct *= scalarOperand;
            scalarOperand = 0.0;
        }
        pendingMultiplicativeOperator.clear();
    }

    /* Risoluzione dell'eventuale operatore di addizione/sottrazione */
    if(!pendingAdditiveOperator.isEmpty()){
        if(scalarOperand != 0.0 || tempProduct != 0.0)
            abortOperation(Exception("Cannot add a scalar to a matrix"));

        Matrix* tempSum = matrixSum;
        if(operand){
            Matrix* tempOperand = operand;
            try{
                if(pendingAdditiveOperator == "+")
                    matrixSum = *tempSum + *tempOperand;
                if(pendingAdditiveOperator == "-")
                    matrixSum = *tempSum - *tempOperand;
            }
            catch(const Exception& error){
                abortOperation(error);
                return;
            }
            operand = 0;
            delete tempOperand;
        }
        if(matrixFactor){
            Matrix* tempFactor = matrixFactor;
            try{
                if(pendingAdditiveOperator == "+")
                    matrixSum = *tempSum + *tempFactor;
                if(pendingAdditiveOperator == "-")
                    matrixSum = *tempSum - *tempFactor;
            }
            catch(const Exception& error){
                abortOperation(error);
                return;
            }
            matrixFactor = 0;
            delete tempFactor;
        }
        delete tempSum;
        pendingAdditiveOperator.clear();
    }

    if(matrixSum){
        operand = matrixSum;
        matrixSum = 0;
    }

    if(matrixFactor){
        operand = matrixFactor;
        matrixFactor = 0;
    }

    if(tempProduct != 0.0){
        scalarOperand = tempProduct;
        tempProduct = 0.0;
    }
    displayMatrix();
}

/*
 * Il metodo clear() resetta lo stato dell'oggetto di invocazione MatrixCalculator
 * allo stato iniziale.
 */

void MatrixCalculator::clear(){
    display->setText("");
    if(operand){
        Matrix* temp = operand;
        operand = 0;
        delete temp;
    }
    if(matrixSum){
        Matrix* temp = matrixSum;
        matrixSum = 0;
        delete temp;
    }
    if(matrixFactor){
        Matrix* temp = matrixFactor;
        matrixFactor = 0;
        delete temp;
    }
    scalarOperand = 0.0;
    tempProduct = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    waitingForOperand = true;
    rowNumber = 0;
    columnNumber = 0;
}

/*
 * Il metodo setRows(value) setta il numero di righe della matrice
 * che si sta inserendo a value; questo valore viene preso da un
 * oggetto QLineEdit.
 */

void MatrixCalculator::setRows(const QString& value) {
    unsigned int temp = value.toUInt();
    rowNumber = temp;
}

/*
 * Il metodo setColumns(value) setta il numero di colonne della matrice
 * che si sta inserendo a value; questo valore viene preso da un
 * oggetto QLineEdit.
 */

void MatrixCalculator::setColumns(const QString& value) {
    unsigned int temp = value.toUInt();
    columnNumber = temp;
}

/*
 * insertValues() crea un nuovo QMessageBox per l'inserimento dei valori della matrice che si sta creando,
 * e in base al suo numero di righe e di colonne crea altrettanti oggetti QLineEdit per inserire i singoli valori.
 */

void MatrixCalculator::insertValues() {
    /* Caso in cui sia stata inserita una matrice/uno scalare appena prima di questo */
    if(!waitingForOperand){
        if(operand){
            Matrix* tempOperand = operand;
            operand = 0;
            delete tempOperand;
        }
        if(scalarOperand != 0.0)
            scalarOperand = 0.0;
    }
    QMessageBox* valuesWindow = new QMessageBox;
    QGridLayout* valuesLayout = new QGridLayout;
    if(rowNumber == 0 || columnNumber == 0)
        return;
    if(rowNumber == 1 && columnNumber == 1){
        valuesWindow->setWindowTitle("SCALAR");
        QLineEdit* num = new QLineEdit(valuesWindow);
        num->setFixedSize(40, 20);
        num->setAlignment(Qt::AlignRight);
        num->setInputMask("000.00");
        connect(num, SIGNAL(textEdited(const QString&)), this, SLOT(setValue(const QString&)));
        connect(num, SIGNAL(returnPressed()), valuesWindow, SLOT(close()));
        connect(num, SIGNAL(returnPressed()), this, SLOT(displayMatrix()));
        valuesLayout->addWidget(num, 1, 1, 1, 1);
    }
    else{
        if(rowNumber == 1)
            operand = new RowVector(columnNumber);
        if(columnNumber == 1)
            operand = new ColumnVector(rowNumber);
        if(rowNumber == columnNumber)
            operand = new SquareMatrix(rowNumber);
        if(rowNumber != 1 && columnNumber != 1 && rowNumber != columnNumber)
            operand = new Matrix(rowNumber, columnNumber);
        QLineEdit* values[rowNumber][columnNumber];

        for(unsigned int i = 0; i < rowNumber; ++i){
            for(unsigned int j = 0; j < columnNumber; ++j){
                values[i][j] = new QLineEdit(valuesWindow);
                values[i][j]->setFixedSize(40, 20);
                values[i][j]->setAlignment(Qt::AlignRight);
                values[i][j]->setInputMask("#00.00");
                values[i][j]->setProperty("row", i);
                values[i][j]->setProperty("column", j);

                connect(values[i][j], SIGNAL(textEdited(const QString&)), this, SLOT(setValue(const QString&)));
                connect(values[i][j], SIGNAL(returnPressed()), valuesWindow, SLOT(close()));
                connect(values[i][j], SIGNAL(returnPressed()), this, SLOT(displayMatrix()));
                valuesLayout->addWidget(values[i][j], i, j, 1, 1);
            }
        }
    }
    Button* next = new Button("Next", valuesWindow);
    valuesLayout->addWidget(next, rowNumber + 1, columnNumber/2, 1, 1);
    connect(next, SIGNAL(clicked()), valuesWindow, SLOT(close()));
    connect(next, SIGNAL(clicked()), this, SLOT(displayMatrix()));
    delete valuesWindow->layout();
    valuesWindow->setLayout(valuesLayout);
    valuesWindow->show();
}

/*
 * Il metodo setValue(value) controlla se si sta inserendo uno scalare o una matrice:
 * nel caso di uno scalare setta il valore di scalarOperand a value;
 * nel caso di una matrice setta il valore dell'elemento [row][column] a value.
 * Gli indici dell'elemento sono individuati dall'oggetto QLineEdit che invoca questo metodo.
 */

void MatrixCalculator::setValue(const QString& value){
    if(rowNumber == 1 && columnNumber == 1)
        scalarOperand = value.toDouble();
    else{
        QLineEdit* edited = qobject_cast<QLineEdit*>(sender());
        operand->setValue(edited->property("row").toUInt(), edited->property("column").toUInt(), value.toDouble());
    }
}

/*
 * Il metodo displayMatrix() visualizza nel display tutte le matrici e gli scalari su cui
 * si possono compiere operazioni, inclusi gli operatori cliccati.
 */

void MatrixCalculator::displayMatrix(){
    display->setText("");

    if(matrixSum){
        for(unsigned int i = 0; i < matrixSum->getRows(); ++i){
            for(unsigned int j = 0; j < matrixSum->getColumns(); ++j)
                display->setText(display->toPlainText() + QString("%1").arg(matrixSum->getValue(i, j), 10, 'f', 2));
            display->setText(display->toPlainText() + "\n");
        }

        display->setText(display->toPlainText() + pendingAdditiveOperator + "\n");
        waitingForOperand = true;
    }

    if(tempProduct != 0.0 || matrixFactor){
        if(tempProduct != 0.0)
            display->setText(display->toPlainText() + QString::number(tempProduct) + "\n");
        if(matrixFactor)
            for(unsigned int i = 0; i < matrixFactor->getRows(); ++i){
                for(unsigned int j = 0; j < matrixFactor->getColumns(); ++j)
                    display->setText(display->toPlainText() + QString("%1").arg(matrixFactor->getValue(i, j), 10, 'f', 2));
                display->setText(display->toPlainText() + "\n");
            }

        display->setText(display->toPlainText() + pendingMultiplicativeOperator + "\n");
        waitingForOperand = true;
    }

    if(scalarOperand != 0.0 || operand){
        if(scalarOperand != 0.0)
            display->setText(display->toPlainText() + QString::number(scalarOperand) + "\n");
        if(operand){
            for(unsigned int i = 0; i < operand->getRows(); ++i){
                for(unsigned int j = 0; j < operand->getColumns(); ++j)
                    display->setText(display->toPlainText() + QString("%1").arg(operand->getValue(i, j), 9, 'f', 2));
                display->setText(display->toPlainText() + "\n");
            }
        }
        rowNumber = 0;
        columnNumber = 0;
        waitingForOperand = false;
    }
}

/*
 * Il metodo abortOperation(error) invoca il metodo clear(), e poi visualizza
 * un messaggio d'errore in base al tipo di eccezione error.
 */

void MatrixCalculator::abortOperation(const Exception& error){
    clear();
    QMessageBox* errorWindow = new QMessageBox;
    errorWindow->setWindowTitle("ERROR");
    errorWindow->setText(error.getType());
    errorWindow->show();
}
