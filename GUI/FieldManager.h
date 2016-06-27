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
    bool currentlyUpdating = false;

public:
    Sudoku sudoku;

    FieldManager(QGridLayout* f);
    ~FieldManager();

public slots:
    void debugEdit(const QString& text) {
        QLineEditID* send = dynamic_cast<QLineEditID*>(sender());
        if (send && !currentlyUpdating) {
            int val = 0;
            if(text.length()>0)
                val = text.toInt();

            sudoku.setAtIndex(send->getID(), val);
            showMessage("Sudoku edited to fit change at id "+std::to_string(send->getID()));
        }
    }

    void updateField() {
        currentlyUpdating = true;
        for(QLineEditID* i : items) {
            QString tmp("");
            if(sudoku.getAtIndex(i->getID()) != NAF)
                tmp = QString::number(sudoku.getAtIndex(i->getID()));
            i->setText(tmp);
        }
        currentlyUpdating = false;
    }
};

#endif // FIELDMANAGER_H
