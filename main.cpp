#include <QApplication>
#include <QGuiApplication>
#include <iostream>

#include <list>

#include "GUI/mainwindow.h"
#include "Generator/SudokuGen.h"
#include "Generator/GenSudoku.h"
#include "Generator/SudokuSolver.h"
#include "Generator/LasVegasAlgo.h"
#include "Generator/SudokuProp.h"
#include "Saver/SaveVector.h"
#include "Saver/SaveIMG.h"

#include <QString>
#include <QRegExp>


#define elif else if

int main(int argc, char *argv[]) {

    int mode = 0;

    if(mode == 0) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        
        return a.exec();
    } elif (mode == 1) {
        GenSudoku s;
        //s.Sudoku::setAtIndex(1,1);
        std::cout << s.toString() << std::endl;

        //std::list<GenSudoku> ret = s.expand();
        //for(std::list<GenSudoku>::iterator i=ret.begin(); i!=ret.end(); i++)
        //    std::cout<< i->toString() << std::endl;

        /*SudokuSolver::DFSLV(s,0,-1, 1);
        std::cout << SudokuSolver::getLastField().toString() << std::endl;

        SudokuSolver::DFSLV(s,0,-1,  10000);
        std::cout << SudokuSolver::getLastField().toString() << std::endl;*/
    } elif (mode == 2) {
        Sudoku su = SudokuGen::digHoles(LasVegasAlgo(), Level::Evil);
        std::cout << SudokuSolver::solutions(GenSudoku(su)) << std::endl;
        std::cout << su.toString() << std::endl;

        su = SudokuProp::propagate(su, 10);
        std::cout << SudokuSolver::solutions(GenSudoku(su)) << std::endl;
        std::cout << su.toString() << std::endl;
    } elif (mode == 3) {
        GenSudoku su;
        char field[81] = {
                3,1,4,5,6,2,7,8,9,
                2,5,6,9,7,8,1,3,4,
                7,9,8,3,1,4,2,5,6,
                1,2,7,8,9,3,4,6,5,
                5,6,9,2,4,7,3,1,8,
                4,8,3,1,5,6,9,2,7,
                9,7,2,6,8,1,5,4,3,
                8,4,1,7,3,5,6,9,2,
                6,3,5,4,2,9,8,7,1};
        std::memcpy(su.getField(), field, sizeof(char)*81);

        Sudoku retS = SudokuGen::digHoles(su, Evil);
        GenSudoku ret = static_cast<GenSudoku>(retS);
        std::cout << ret.getTotalCells() << std::endl;

        // He gets 25
    } elif(mode == 4) {
        GenSudoku su;
        char field[81] = {
                0,0,0,0,0,0,0,0,0,
                0,0,0,5,7,8,1,3,4,
                7,9,8,3,1,4,2,5,6,
                1,2,7,8,9,3,4,6,5,
                5,6,9,2,4,7,3,1,8,
                4,8,3,1,5,6,9,2,7,
                9,7,2,6,8,1,5,4,3,
                8,4,1,7,3,5,6,9,2,
                6,3,5,4,2,9,8,7,1
        };

        std::memcpy(su.getField(), field, sizeof(char)*81);
        std::cout << printBool(SudokuSolver::solvable(su)) << std::endl;
    } elif(mode == 5) {
        QGuiApplication a(argc, argv);
        Sudoku su = LasVegasAlgo();
        SaveVector::SavePDF(su, "/Users/Georg/Desktop/out.pdf");
        SaveVector::SaveSVG(su, "/Users/Georg/Desktop/out.svg");

        SaveIMG::save(su, "/Users/Georg/Desktop/out.png");
        SaveIMG::save(su, "/Users/Georg/Desktop/out.tiff");
        SaveIMG::save(su, "/Users/Georg/Desktop/out.jpg");
    } elif(mode == 6) {
        QVector<QString> tests;
        tests << "bla.png" << "png.jpg" << ".png.pdf" << ".jpg.pdf";
        for(QString &test : tests) {
            std::cout << printBool(test.contains(QRegExp("\\.(?:png|jpg)$"))) << std::endl;
        }
    }

    return 0;
}
