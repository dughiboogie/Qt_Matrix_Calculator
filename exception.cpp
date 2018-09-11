#include "exception.h"

/*
 * Costruttore ad un argomento, che corrisponde al tipo di eccezione.
 */

Exception::Exception(const QString& t) : type(t) { }

/*
 * Metodo get per il tipo di eccezione per cui l'oggetto attuale è stato creato.
 */

QString Exception::getType() const{
    return type;
}
