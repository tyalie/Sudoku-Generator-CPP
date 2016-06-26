#include <QApplication>
#include <iostream>

#include <list>

#include "GUI/mainwindow.h"
#include "Generator/GenSudoku.h"
#include "Generator/SudokuSolver.h"

int main(int argc, char *argv[]) {
    int mode = 1;

    if(mode == 0) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        w.adjustSize();
        w.setFixedSize(w.size());

        return a.exec();
    } if(mode == 1) {
        /*GenSudoku s;
        //s.Sudoku::setAtIndex(1,1);
        std::cout << s.toString() << std::endl;

        //std::list<GenSudoku> ret = s.expand();
        //for(std::list<GenSudoku>::iterator i=ret.begin(); i!=ret.end(); i++)
        //    std::cout<< i->toString() << std::endl;

        SudokuSolver::DFSLV(s, 2);
        std::cout << SudokuSolver::getLastField().toString() << std::endl;*/
    }

    return 0;
}
