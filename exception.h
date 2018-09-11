#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>

class Exception {
    QString type;
public:
    Exception(const QString& type);
    QString getType() const;
};

#endif // EXCEPTION_H
