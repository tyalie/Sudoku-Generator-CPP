#include "Saver/SaveHandler.h"

QString SaveHandler::fileName = "";
QString SaveHandler::filter = PDF;

SaveHandler::SaveHandler( Sudoku su, QWidget *parent) {
    QString path = QFileDialog::getSaveFileName(parent, "Select position to Save",
        fileName,  PDF SP SVG SP IMG SP TXT, &filter);

    if(path.length()==0)
        return;

    fileName = path;

    if(fileName.endsWith("."))
        fileName.chop(1);

    if(!filter.compare(TXT))
        SaveTXT(su, fileName);
    elif(!filter.compare(SVG))
        SaveVector::SaveSVG(su, fileName);
    elif(!filter.compare(PDF))
        SaveVector::SavePDF(su, fileName);
    elif(!filter.compare(IMG))
        SaveIMG::save(su, fileName.contains(QRegExp(IMGE))?fileName:(fileName+".png"));
}
