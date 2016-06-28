#include "Saver/StackSave.h"

StackData StackSave::request;

void StackSave::processSudoku(QByteArray &elem) {
    try {
        Sudoku su = StaticGenerator(request.level);
        elem.append(su.getField(), 81);
    } catch(std::exception &e) {}
}

StackSave::StackSave(StackData in) {
    request = in;
    showMessage("StackSave takes now over with count of " + std::to_string(in.number) +
        "\n               and level " + getInfo(in.level).name);
    QList<QByteArray> list;
    for(int i=0;i<in.number;i++)
        list.append(QByteArray());

    dialog = new QProgressDialog();
    dialog->setLabelText(QString(PROGRESS_TEXT " 0/%1").arg(in.number));

    ThreadManager manager;

    QFutureWatcher<void> futureWatcher;
    QObject::connect(&futureWatcher, SIGNAL(finished()), dialog, SLOT(reset()));
    QObject::connect(dialog, SIGNAL(canceled()), &manager, SLOT(cancel()));
    QObject::connect(dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
    QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), dialog, SLOT(setRange(int,int)));
    QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), dialog, SLOT(setValue(int)));
    QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), this, SLOT(changeDialog(int)));

    futureWatcher.setFuture(QtConcurrent::map(list, &StackSave::processSudoku));
    dialog->exec();
    futureWatcher.waitForFinished();

    showMessage("StackSave- Finished");
    if(!futureWatcher.future().isCanceled()) {
        save:
        in.number = futureWatcher.progressValue();
        SaveOpenSudoku(list, in);
    } else if(futureWatcher.progressValue()>0 ){
        showMessage("StackSave- User canceled operation");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, "Still save", "You canceled the calculation thread.\n"
            "Do you still want to save the processed ones?", QMessageBox::Yes|QMessageBox::No);

        if(reply == QMessageBox::Yes)
            goto save;
    }
}


#define HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define BEGIN "<opensudoku>\n  <source>Sudoku creator by Georg A. Friedrich</source>\n"
#define NAME(NOM) "  <name>"<<NOM<<"</name>\n"
#define AUTHOR(NOM) "  <author>"<<NOM<<"</author>\n"
#define CREATED(DATE) "  <created>"<<DATE<<"</created>\n"
#define LEVEL(L) "  <level>"<<L<<"</level>\n"
#define DATAB "  <game data=\""
#define DATAE "\" />\n"
#define END "</opensudoku>\n"

bool StackSave::SaveOpenSudoku(QList<QByteArray> in, StackData request) {

    QFile file(request.path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadWrite))
        return false;

    file.resize(0);

    std::stringstream ret;
    ret << HEADER << BEGIN << NAME(request.name.toStdString());
    ret << AUTHOR(request.author.toStdString());
    ret << LEVEL(getInfo(request.level).name);

    char buffer [80];
    std::time_t t = std::time(0);
    strftime(buffer, 80, "%F", std::localtime(&t));
    ret << CREATED(buffer);

    for (QByteArray &i : in) {
        if(i.size()==81) {
            ret << DATAB;
            for(int j = 0; j < i.size(); j++)
                ret << (int)i[j];
            ret << DATAE;
        }
    }

    ret << END;

    return (file.write(ret.str().c_str())<ret.str().size());

}
