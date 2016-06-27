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
#include "GUI/ThreadManager.h"
#include "GUI/ThreadTrigger.h"

#include <QMainWindow>
#include <QString>
#include <QGridLayout>
#include <QObject>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

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

    QFuture<ReturnType> future;
    QFutureWatcher<ReturnType> *watcher;
    ThreadManager *tm;

    void startWithFuture(QFuture<ReturnType> mFuture);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

    void generate();
    void terminalPattern();
    void solve();
    void solveAll();
    void handleFinished();


    void clear() {
        showMessage("Clear Button pressed\n");
        manager->sudoku = GenSudoku();
        manager->updateField();
    }

    void quitB() {
        showMessage("Goodbye!\n\n");
        QApplication::quit();
    }
};

#endif // MAINWINDOW_H
