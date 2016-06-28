#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include "Commons/common.h"
#include "GUI/QLineEditID.h"
#include "GUI/QStrictIntValidator.h"
#include "Generator/GenSudoku.h"
#include "Sudoku/Sudoku.h"

#include <QObject>
#include <QString>
#include <QGridLayout>
#include <QPalette>

#include <array>
#include <iostream>
#include <string>


class FieldManager : public QObject {
    Q_OBJECT

private:
    bool shortcut= false;
    QGridLayout* field;
    std::array<QLineEditID*,81> items;

public:
    Sudoku sudoku;

    FieldManager(QGridLayout* f);
    ~FieldManager();
    QPalette pals[2] = {QPalette(), QPalette()};

public slots:
    void debugEdit(const QString& text) {
        QLineEditID* send = dynamic_cast<QLineEditID*>(sender());
        if (send) {
            int val = 0;
            if(text.length()>0) {
                val = text.toInt();
                checking:
                items[ (send->getID()+1)%items.size() ]->getFocus();
            } else if(shortcut)
                goto checking;

            sudoku.setAtIndex(send->getID(), val);

            GenSudoku gen(sudoku);
            auto pos = gen.getInvalid();
            for(int i=0; i<pos.size();i++) {
                items[i]->setPalette(pals[!pos[i]]);
                items[i]->setAutoFillBackground(true);
            }
        }
    }

    void updateField() {
        for(QLineEditID* i : items) {
            QString tmp("");
            if(sudoku.getAtIndex(i->getID()) != NAF)
                tmp = QString::number(sudoku.getAtIndex(i->getID()));
            i->setText(tmp);
        }
        GenSudoku gen(sudoku);
        auto pos = gen.getInvalid();
        for(int i=0; i<pos.size();i++) {
            items[i]->setPalette(pals[!pos[i]]);
            items[i]->setAutoFillBackground(true);
        }
    }

    void changeShort(int state) {
        shortcut = (state == Qt::Checked);
    }
};

#endif // FIELDMANAGER_H
