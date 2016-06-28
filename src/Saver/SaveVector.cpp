#include "Saver/SaveVector.h"

void SaveVector::paint(Sudoku &su, QPainter& paint, int offset, int tilesize) {
    QPen penN = PEN(0x90, 0x90, 0x90,tilesize/50.0, Qt::CustomDashLine);
    QPen penC = PEN(0x00,0x00,0x00, tilesize/20.0, Qt::SolidLine);

    int multi = 1;

    QVector<qreal> dashes;
    dashes << tilesize / 4.0 << tilesize / 4.0;
    penN.setDashPattern(dashes);
    penN.setDashOffset(tilesize/8.0);
    paint.setPen(penN);
paint:
    for(int i=1; i<9/multi; i++) {
        if (!(i%3))
            continue;
        paint.drawLine(offset + tilesize*multi*i, offset, offset + tilesize*multi*i, offset + tilesize*9);
        paint.drawLine(offset, offset + tilesize*multi*i, offset+tilesize*9, offset + tilesize*multi*i);
    }

    paint.setPen(penC);
    if(!(multi-1)) {
        multi = 3;
        goto paint;
    }

    QFont font("times", 0.5*tilesize);
    font.setBold(true);

    paint.setFont(font);
    QFontMetrics fm(font);

    for(int i=0; i< 81; i++) {
        if(su.getAtIndex(i)>0) {
            QString c = QString::number(su.getAtIndex(i));
            int cx = tilesize/2 - fm.width(c)/2;
            int cy = tilesize - fm.height()/2;

            paint.drawText(offset+(i%9)*tilesize+cx, offset+i/9*tilesize+cy, c);
        }
    }
}

bool SaveVector::SaveSVG(Sudoku su, QString path) {
    QSvgGenerator svg;
    svg.setFileName(path);
    svg.setSize(QSize(500, 500));
    svg.setViewBox(QRect(0,0,SIZE(5,20)));

    QPainter painter;
    painter.begin(&svg);
    paint(su, painter);
    painter.end();

    return true;
}

bool SaveVector::SavePDF(Sudoku su, QString path) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    printer.setFullPage(true);
    printer.setPaperSize(QSizeF(SIZE(5,20)), QPrinter::DevicePixel);

    QPainter painter;
    painter.begin(&printer);
    paint(su, painter);
    painter.end();

    return false;
}
