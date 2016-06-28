#include "FieldManager.h"

#define W 9
#define S (W*W)

FieldManager::FieldManager(QGridLayout* f) {
    field = f;

    QValidator *val = new QStrictIntValidator(1,9, 0);
    for(int i=0;i<S;i++) {
        std::string prop("");
        QLineEditID* a = new QLineEditID(i, 0);
        items[i] = a;
        a->setValidator(val);
        a->setFixedSize(30,30);
        a->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        prop+="border: 1px solid gray;";
        if(i%3==0) prop+="border-left-color: black;";
        if(i%3==2) prop+="border-right-color: black;";
        if((i/9)%3==0) prop+="border-top-color: black;";
        if((i/9)%3==2) prop+="border-bottom-color: black;";

        a->setStyleSheet( (std::string("QLineEdit {background:rgba(0,0,0,0); border:none;")+prop+"}").c_str() ) ;
        field->addWidget(a,i/W,i%W);
        a->show();

        // TODO: this is debug
        QObject::connect(a, SIGNAL(textEdited(QString)), this, SLOT(debugEdit(QString)));
    }

    pals[0].setColor(items[0]->backgroundRole(), QColor(254, 114, 85));
    pals[1].setColor(items[0]->backgroundRole(), QColor(0,0,0,0));
    
    field->setSpacing(0);
    field->update();

}

FieldManager::~FieldManager() {
    for(QLineEditID* i : items)
        delete i;
}
