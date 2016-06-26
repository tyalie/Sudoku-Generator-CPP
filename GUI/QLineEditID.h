#include <QLineEdit>

class QLineEditID : public QLineEdit {
private:
    int ID;
    
public:
    QLineEditID(int ID, QWidget * parent = 0) : QLineEdit(parent) {
        this->ID = ID;
    }
    
    int getID() const {
        return ID;
    }
};