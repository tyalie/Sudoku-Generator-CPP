#include "ThreadManager.h"

bool ThreadManager::abort = false;

ThreadManager::ThreadManager(QWidget *parent) {
    msg = new QMessageBox;
    abort = false;
    msg->setText("This can take longer. Please wait…");
    //msg->setModal(true);
    msg->setWindowModality(Qt::ApplicationModal);
    msg->setStandardButtons(QMessageBox::Cancel);
    QCoreApplication::processEvents();
    msg->show();
    QCoreApplication::processEvents();
    QObject::connect(msg, SIGNAL(buttonClicked(QAbstractButton*)),
        this, SLOT(cancel(QAbstractButton*)));
}

ThreadManager::ThreadManager() {
    abort = false;
}

ThreadManager::~ThreadManager() {
    if(msg)
        delete msg;
    abort = false;
}
