#include "stacksavedialog.h"
#include "ui_stacksavedialog.h"

QString StackSaveDialog::path = QDir::homePath() + "/";

StackSaveDialog::StackSaveDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::StackSaveDialog) {
    ui->setupUi(this);

    for(int i = Level::ExtremlyEasy; i<=Level::Evil; i++) {
        Level l = static_cast<Level>(i);
        ui->difficultyC->addItem(QString( getInfo(l).name.c_str() ));
    }
    ui->saveL->setText(path);

    QObject::connect(ui->fileChooserB, SIGNAL(clicked()), this, SLOT(extSaveLocation()));
    QObject::connect(ui->nameL, SIGNAL(textEdited(QString)), this, SLOT(nameChanged(QString)));
    QObject::connect(ui->saveL, SIGNAL(textEdited(QString)), this, SLOT(dirChanged(QString)));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(startStack()));

    setFixedSize(size());
}

StackSaveDialog::~StackSaveDialog() {
    delete ui;
}

void StackSaveDialog::extSaveLocation()  {
    QString tmp = QFileDialog::getSaveFileName(this, "Select position to save",
        path, "OpenSudoku (*.opensudoku)");
    if(tmp.length()==0)
        return;
    path = tmp;
    ui->saveL->setText(path);
}

QString StackSaveDialog::toCamelCase(QString camelCase) {
    int i = -1;
    while( (i = camelCase.indexOf(QRegExp("[^a-zA-Z0-9]"))) + 1) {
        camelCase.remove(i, 1);
        if(camelCase.length()>i)
            camelCase[i] = camelCase[i].toUpper();
    }
    return camelCase;
}

void StackSaveDialog::nameChanged(QString name) {
    pureName = !name.length();
    if(!pureURI)
        return;

    QString camelCase = toCamelCase(name);
    ui->saveL->setText(ui->saveL->text().replace(QRegExp("\\/[^\\/]*$"), "/"+camelCase + ".opensudoku"));
}

void StackSaveDialog::dirChanged(QString dir) {
    pureURI = true;
    if(!dir.contains(QRegExp("\\/[^\\/]*\\.opensudoku$")))
        if(dir.replace(QRegExp("\\/[^\\/]*$"), "/"+toCamelCase(ui->nameL->text()) + ".opensudoku") != dir)
            pureURI = false;

    if(!pureName)
        return;
    QString name = dir.remove(QRegExp("\\.[^\\.]+$")).remove(0, dir.lastIndexOf("/"));
    ui->nameL->setText(name.remove(QRegExp("[^a-zA-Z0-9 ]")));
}

void StackSaveDialog::startStack() {
    accept();
    StackData data;
    data.number = ui->sudokuS->value();
    data.level  = static_cast<Level>(ui->difficultyC->currentIndex());
    data.author = ui->authorL->text();
    data.name   = ui->nameL->text();
    data.path   = ui->saveL->text();
    StackSave save(data);
}
