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

    QMessageBox *msg;

    ThreadManager(QWidget* parent = 0) {
        msg = new QMessageBox;
        abort = false;
        msg->setText("You're waiting.");
        //msg->setModal(true);
        msg->setWindowModality(Qt::ApplicationModal);
        msg->setStandardButtons(QMessageBox::Cancel);
        QCoreApplication::processEvents();
        msg->show();
        QCoreApplication::processEvents();
        QObject::connect(msg, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(cancel(QAbstractButton*)));
    }

    ~ThreadManager() {
        delete msg;
        abort = false;
    }

public slots:
    void cancel(QAbstractButton *button) {
        abort = true;
    }
};

#endif // THREADMANAGER_H
