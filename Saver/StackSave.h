#ifndef STACKSAVE_H
#define STACKSAVE_H

#include "Commons/common.h"
#include "Generator/GenSudoku.h"
#include "Generator/StaticGenerator.h"
#include "Saver/SaveHandler.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrentMap>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QFuture>

#include <sstream>
#include <string>
#include <ctime>

#define PROGRESS_TEXT "Create Sudokus. Please wait… "

struct StackData {
    int number;
    Level level;
    QString author;
    QString name;
    QString path;
};

class StackSave : public QObject {
    Q_OBJECT
private:
    static StackData request;
    QProgressDialog *dialog;

    static void processSudoku(QByteArray&);

public:
    StackSave(StackData);
    ~StackSave() { delete dialog; }
    static bool SaveOpenSudoku(QList<QByteArray>, StackData);

public slots:
    void changeDialog(int value) { dialog->setLabelText(QString(PROGRESS_TEXT "%1/%2").arg(value).arg(request.number)); }
};

#endif // STACKSAVE_H
