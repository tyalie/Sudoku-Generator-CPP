#ifndef SAVEPDF_H
#define SAVEPDF_H

#include "Sudoku/Sudoku.h"

#include <QString>
#include <QFile>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QSvgGenerator>
#include <QFontMetrics>
#include <QFont>
#include <QPrinter>
#include <QSizeF>
#include <QPen>

#define PEN(r, g, b, w, style) QPen(QBrush(QColor(r,g,b)), w, style)
#define SIZE(o,t) o*2+t*9, o*2+t*9

class SaveVector {
protected:
    static void paint(Sudoku&, QPainter &, int offset = 5, int tilesize = 20 );
public:
    static bool SavePDF(Sudoku, QString);
    static bool SaveSVG(Sudoku, QString);
};

#endif // SAVEPDF_H
