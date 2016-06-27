#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    manager = new FieldManager(ui->field);

    for(int i = Level::ExtremlyEasy; i<=Level::Evil; i++) {
        Level l = static_cast<Level>(i);
        ui->difficultyList->addItem(QString( getInfo(l).name.c_str() ));
    }

    QObject::connect(ui->genButton, SIGNAL(clicked()), this, SLOT(generate()));
    QObject::connect(ui->clearB, SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(ui->CTPB, SIGNAL(clicked()), this, SLOT(terminalPattern()));
    QObject::connect(ui->solveB, SIGNAL(clicked()), this, SLOT(solve()));
    QObject::connect(ui->solveAllB, SIGNAL(clicked()), this, SLOT(solveAll()));
    QObject::connect(ui->quitB, SIGNAL(clicked()), this, SLOT(quitB()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete manager;
}

void MainWindow::startWithFuture(QFuture<ReturnType> mFuture) {
    watcher = new QFutureWatcher<ReturnType>;
    Level l = static_cast<Level>(ui->difficultyList->currentIndex());

    if(tm!=nullptr)
        delete tm;
    tm = new ThreadManager;

    QObject::connect(watcher, SIGNAL(finished()), this, SLOT(handleFinished()));

    future = mFuture;
    watcher->setFuture(future);
}

void MainWindow::generate()  {
    showMessage("Generate Button pressed");
    Level l = static_cast<Level>(ui->difficultyList->currentIndex());
    startWithFuture(QtConcurrent::run(startGenerator, l));
}

void MainWindow::terminalPattern() {
    showMessage("CTPB pressed");
    startWithFuture(QtConcurrent::run(startLasVegas));
}

void MainWindow::solve() {
    showMessage("Solve Single button pressed");
    GenSudoku tmp = GenSudoku(manager->sudoku);
    startWithFuture(QtConcurrent::run(solveSudoku, tmp));
}

void MainWindow::solveAll() {
    showMessage("Solve for All Button pressed");
    startWithFuture(QtConcurrent::run(solveForAll, manager->sudoku));
}

void MainWindow::handleFinished() {
    if(tm!=nullptr)
        delete tm;
    tm = nullptr;

    ReturnType ret = future.result();
    if(!ret.sudoku.isInvalid()) {
        manager->sudoku = ret.sudoku;
        manager->updateField();
    }

    if(ret.number>0) {
        QMessageBox msg;
        msg.information(0, "Solutions", "The sudoku has " + QString::number(ret.number) + " solution(s).");
    }

    delete watcher;
    showMessage("Sequence ended \n");
}
