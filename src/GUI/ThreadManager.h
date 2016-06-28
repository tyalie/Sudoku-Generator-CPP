#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#define __abort__ (ThreadManager::getAbort())

#include "Commons/common.h"

#include <QObject>
#include <QMessageBox>
#include <QAbstractButton>
#include <QCoreApplication>
#include <QFuture>

class ThreadManager : public QObject {
    Q_OBJECT

private:
    static bool abort;
public:
    static bool getAbort() {return abort;}

    QMessageBox *msg = nullptr;

    ThreadManager(QWidget*);
    ThreadManager();
    ~ThreadManager();

public slots:
    void cancel(QAbstractButton *button = 0) {
        abort = true;
    }
};

#endif // THREADMANAGER_H
