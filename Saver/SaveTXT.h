#ifndef SAVETXT_H
#define SAVETXT_H

#include "Sudoku/Sudoku.h"

#include <QString>
#include <QFile>
#include <QIODevice>

inline bool SaveTXT(Sudoku su, QString fileName) {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadWrite))
        return false;

    QByteArray data( su.toString().c_str(), su.toString().size() );
    if(file.write(data)<su.toString().size())
        return false;
    return true;
}


#endif // SAVETXT_H
