#ifndef QSTRICTINTVALIDATOR_H
#define QSTRICTINTVALIDATOR_H

#include <QObject>
#include <QIntValidator>

class QStrictIntValidator : public QIntValidator {
    Q_OBJECT

public:
    QStrictIntValidator(int min, int max, QObject *parent)
                : QIntValidator(min, max, parent) {}

    QValidator::State validate(QString &in, int &pos) const {
        QIntValidator::State result(QIntValidator::validate(in, pos));
        if ( in.length() >0 && result == QValidator::Intermediate) result = QValidator::Invalid;
        return result;
    };
};

#endif // QSTRICTINTVALIDATOR_H
