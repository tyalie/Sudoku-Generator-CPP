#ifndef GENSUDOKU_H
#define GENSUDOKU_H

#include "Commons/common.h"
#include "Sudoku/Sudoku.h"

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <bitset>

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

    GenSudoku( Sudoku &obj );

    int getIndex() {return index;}
    void setIndex(int i) {index = i;}

    char getAtIndex() { return field[index]; }
    void setAtIndex(char v) { field[index] = v; }

    void swapIndex(size_t i1, size_t i2) { std::swap(field[i1], field[i2]); }

    bool isIndexLast();
    void moveNext();
    void resetIndex();

    std::list<GenSudoku> expand();
    std::vector<char> getAvailable();
    std::bitset<81> getInvalid();

    GenSudoku digClone(int);

    int getTotalCells();
    int getLowerBoundRC();
};
#endif
