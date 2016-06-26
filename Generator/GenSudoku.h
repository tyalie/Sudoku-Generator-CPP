#ifndef GENSUDOKU_H
#define GENSUDOKU_H

#include "Sudoku/Sudoku.h"
#include <list>
#include <iostream>

class GenSudoku : public Sudoku {
private:
    size_t index;

    bool* rule1_cols(bool*) const;
    bool* rule2_rows(bool*) const;
    bool* rule3_block(bool*) const;

public:
    GenSudoku();

    ~GenSudoku();

    GenSudoku(const GenSudoku &obj );

    char getAtIndex() { return field[index]; }
    void setAtIndex(char v) { field[index] = v; }

    void swapIndex(size_t i1, size_t i2) { std::swap(field[i1], field[i2]); }

    bool isIndexLast();
    void moveNext();

    std::list<GenSudoku> expand();
};
#endif
