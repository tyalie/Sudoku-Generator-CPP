#ifndef SAVEIMG_H
#define SAVEIMG_H

#include "Saver/SaveVector.h"

#include <QRectF>
#include <QRegExp>

#define OFFSET 5*4
#define TILESIZE 20*4

class SaveIMG : private SaveVector {
public:
    static void save(Sudoku su, QString path) {
        QImage img(QSize(SIZE(OFFSET, TILESIZE)), QImage::Format_ARGB32);
        QPainter painter;
        painter.begin(&img);

        QBrush back(QColor(0,0,0,0));
        if(path.contains(QRegExp("(?:jpe?g)")))
            back = QBrush(QColor(0xff,0xff,0xff));

        painter.fillRect(QRectF(0,0, img.width(), img.height()), back);

        paint(su, painter, OFFSET, TILESIZE);
        painter.end();
        img.save(path);
    }
};

#endif // SAVEIMG_H
