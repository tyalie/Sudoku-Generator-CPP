#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "Commons/common.h"

#include "GUI/QLineEditID.h"
#include "GUI/FieldManager.h"


#include "Generator/LasVegasAlgo.h"
#include "Generator/SudokuGen.h"
#include "Generator/SudokuProp.h"
#include "Generator/SudokuSolver.h"
#include "Generator/GenSudoku.h"
#include "Generator/StaticGenerator.h"

#include <QMainWindow>
#include <QString>
#include <QGridLayout>
#include <QObject>

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    FieldManager* manager;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void generate() {
        std::srand(std::time(0));
        Level l = static_cast<Level>(ui->difficultyList->currentIndex());

        manager->sudoku = StaticGenerator(l);;

        manager->updateField();
    }


};

#endif // MAINWINDOW_H
