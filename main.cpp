#include <QApplication>
#include <iostream>

#include <list>

#include "GUI/mainwindow.h"
#include "Generator/SudokuGen.h"
#include "Generator/GenSudoku.h"
#include "Generator/SudokuSolver.h"
#include "Generator/LasVegasAlgo.h"
#include "Generator/SudokuProp.h"

#define elif else if

int main(int argc, char *argv[]) {
    int mode = 2;

    if(mode == 0) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        w.adjustSize();
        w.setFixedSize(w.size());

        return a.exec();
    } elif (mode == 1) {
        GenSudoku s;
        //s.Sudoku::setAtIndex(1,1);
        std::cout << s.toString() << std::endl;

        //std::list<GenSudoku> ret = s.expand();
        //for(std::list<GenSudoku>::iterator i=ret.begin(); i!=ret.end(); i++)
        //    std::cout<< i->toString() << std::endl;

        SudokuSolver::DFSLV(s, 1);
        std::cout << SudokuSolver::getLastField().toString() << std::endl;

        SudokuSolver::DFSLV(s, 10000);
        std::cout << SudokuSolver::getLastField().toString() << std::endl;
    } elif (mode == 2) {
        Sudoku su = SudokuGen::digHoles(LasVegasAlgo(), Level::Evil);
        std::cout << SudokuSolver::solutions(GenSudoku(su)) << std::endl;
        std::cout << su.toString() << std::endl;

        su = SudokuProp::propagate(su, 10);
        std::cout << SudokuSolver::solutions(GenSudoku(su)) << std::endl;
        std::cout << su.toString() << std::endl;
    }

    return 0;
}
