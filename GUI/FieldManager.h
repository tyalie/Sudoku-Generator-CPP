#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include "Commons/common.h"
#include "GUI/QLineEditID.h"
#include "GUI/QStrictIntValidator.h"
#include "Sudoku/Sudoku.h"

#include <QObject>
#include <QString>
#include <QGridLayout>

#include <array>
#include <iostream>
#include <string>


class FieldManager : public QObject {
    Q_OBJECT

private:
    QGridLayout* field;
    std::array<QLineEditID*,81> items;

public:
    Sudoku sudoku;

    FieldManager(QGridLayout* f);
    ~FieldManager();

public slots:
    void debugEdit(const QString& text) {
        //std::cout << text.toUtf8().constData() << std::endl;
    }

    void updateField() {
        for(QLineEditID* i : items) {
            QString tmp("");
            if(sudoku.getAtIndex(i->getID()) != NAF)
                tmp = QString::number(sudoku.getAtIndex(i->getID()));
            i->setText(tmp);
        }
    }
};

#endif // FIELDMANAGER_H
