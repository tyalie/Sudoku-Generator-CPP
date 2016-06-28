#ifndef STACKSAVE_H
#define STACKSAVE_H

#include "Commons/common.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrentMap>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QFuture>

class StackSave : public QObject {
    Q_OBJECT
private:
    static Level level;

    QProgressDialog *dialog;
    int number;

    static void processSudoku(QByteArray&);

public:
    StackSave(int num, Level l) : number(num) {
        level = l;
        showMessage("StackSave takes now over with count of " + std::to_string(num) +
            "\n               and level " + getInfo(l).name);
        QList<QByteArray> list;
        for(int i=0;i<num;i++)
            list.append(QByteArray(81, '\0'));

        dialog = new QProgressDialog();
        dialog->setLabelText(QString("0/%1 sudokus were created.").arg(num));

        QFutureWatcher<void> futureWatcher;
        QObject::connect(&futureWatcher, SIGNAL(finished()), dialog, SLOT(reset()));
        QObject::connect(dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
        QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), dialog, SLOT(setRange(int,int)));
        QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), dialog, SLOT(setValue(int)));

        futureWatcher.setFuture(QtConcurrent::map(list, &StackSave::processSudoku));
        dialog->exec();
        futureWatcher.waitForFinished();

        if(!futureWatcher.future().isCanceled()) {
            save:
            SaveOpenSudoku(list, futureWatcher.progressValue());
        } else if(futureWatcher.progressValue()>0 ){
            showMessage("StackSave- User canceled operation");
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, "Still save", "You canceled the calculation thread.\n"
                "Do you still want to save the processed ones?", QMessageBox::Yes|QMessageBox::No);

            if(reply == QMessageBox::Yes)
                goto save;
        }

    }

    ~StackSave() {
        delete dialog;
    }

    static void SaveOpenSudoku(QList<QByteArray>, int max=-1);
};

#endif // STACKSAVE_H
