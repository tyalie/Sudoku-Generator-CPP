#include "Saver/SaveHandler.h"

QString SaveHandler::fileName = "";

SaveHandler::SaveHandler( Sudoku su, QWidget *parent) {
    QString filter = TXT;

    fileName = QFileDialog::getSaveFileName(parent, "Select file to Save",
        fileName,  PDF SP SVG SP IMG SP TXT, &filter);

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


    std::cout << filter.toUtf8().constData() << std::endl;
}
