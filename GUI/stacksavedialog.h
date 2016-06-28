#ifndef STACKSAVEDIALOG_H
#define STACKSAVEDIALOG_H

#include "Saver/StackSave.h"
#include "Commons/common.h"

#include <QFileDialog>
#include <QDialog>
#include <QRegExp>
#include <QString>
#include <QDir>

namespace Ui {
class StackSaveDialog;
}

class StackSaveDialog : public QDialog {
    Q_OBJECT

private:
    static QString path;
    Ui::StackSaveDialog *ui;
    bool pureURI = true;
    bool pureName = true;
    
    QString toCamelCase(QString);

public:
    explicit StackSaveDialog(QWidget *parent = 0);
    ~StackSaveDialog();

private slots:
    void extSaveLocation();
    void nameChanged(QString);
    void dirChanged(QString);
    void startStack();
};

#endif // STACKSAVEDIALOG_H
