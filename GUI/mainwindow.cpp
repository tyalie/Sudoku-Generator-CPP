#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    manager = new FieldManager(ui->field);

    for(int i = Level::ExtremlyEasy; i<=Level::Evil; i++) {
        Level l = static_cast<Level>(i);
        ui->difficultyList->addItem(QString( getInfo(l).name.c_str() ));
    }

    QObject::connect(ui->genButton, SIGNAL(clicked()), this, SLOT(generate()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete manager;
}
