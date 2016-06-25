#include <QApplication>

#include "GUI/mainwindow.h"

int main(int argc, char *argv[]) {
    int mode = 0;
    
    if(mode == 0) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        w.adjustSize();
        w.setFixedSize(w.size());

        return a.exec();
    } if(mode == 1) {
    }
    
    return 0;
}
