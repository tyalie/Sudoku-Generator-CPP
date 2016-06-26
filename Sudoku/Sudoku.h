#ifndef SUDOKU_H
#define SUDOKU_H

#include "Commons/common.h"
#include <sstream>
#include <string>

#define STATIC_INDEX(x,y) (x + 9 * y)

class Sudoku {
protected:
    char field[TOTAL];
public:
    Sudoku() {
        std::memset(field, NAF, sizeof(field));
    }

    ~Sudoku() {
    }

    Sudoku(const Sudoku &obj) {
        std::memcpy(field, obj.field, sizeof(field));
    }

    char getAtIndex(size_t i) const {
        return field[i];
    }

    void setAtIndex(size_t i, char v) {
        field[i] = v;
    }

    std::string toString() {
        std::stringstream out;
        for (int i = 0; i < TOTAL; i++) {
            if (i != 0) {
                if (i % (DIM_F * DIM_B) == 0)
                    out << "\n-------|-------|-------\n";
                else if (i % DIM_F == 0)
                    out << "\n";
                else if (i % DIM_B == 0)
                    out << " |";
            }
            out << " ";

            if (field[i] != NAF) {
                out << std::to_string(field[i]);
            } else
                out << " ";
        }
        out<<"\n";
        return out.str();
    }

    char* getField() {
        return field;
    }
};

#endif // SUDOKU_H
