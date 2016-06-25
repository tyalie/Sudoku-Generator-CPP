#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <QIntValidator>
#include <QGridLayout>
#include <QObject>

#define W 9
#define S W*W

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    using namespace std;

    ui->setupUi(this);

    QValidator *val = new QIntValidator(0,9, this);
    for(int i=0;i<S;i++) {
        string prop("");
        QLineEditID* a = new QLineEditID(i, this);
        items[i] = a;
        a->setValidator(val);
        a->setFixedSize(30,30);
        a->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        prop+="border: 1px solid gray;";
        if(i%3==0) prop+="border-left-color: black;";
        if(i%3==2) prop+="border-right-color: black;";
        if((i/9)%3==0) prop+="border-top-color: black;";
        if((i/9)%3==2) prop+="border-bottom-color: black;";

        a->setStyleSheet( (string("QLineEdit {background:rgba(0,0,0,0); border:none;")+prop+"}").c_str() ) ;
        ui->field->addWidget(a,i/W,i%W);
        a->show();

        // TODO: this is debug
        QObject::connect(a, SIGNAL(textChanged(QString)), this, SLOT(debugEdit(QString)));
    }

    ui->field->setSpacing(0);
    ui->field->update();
}

MainWindow::~MainWindow() {
    delete ui;
    for(QLineEditID* i : items)
        delete i;
}
