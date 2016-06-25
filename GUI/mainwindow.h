#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QLineEditID.h"

#include <iostream>
#include <QMainWindow>
#include <QString>
#include <qDebug>
#include <array>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void debugEdit(const QString& text) {
        qDebug() << text;
    }

private:
    std::array<QLineEditID*,81> items;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
