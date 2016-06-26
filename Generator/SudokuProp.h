#ifndef SUDOKUPROP_H
#define SUDOKUPROP_H

#include "Generator/GenSudoku.h"

#include <cstdlib>
#include <ctime>

class SudokuProp {
private:
    static bool prop1_2Digits(Sudoku&, char, char);
    static bool prop2_2ColumnInBlock(Sudoku&, char, char, char);
    static bool prop3_2ColumnOfBlock(Sudoku&, char, char);
    static bool prop4_GridRoll(Sudoku&, unsigned int);

public:
    static Sudoku propagate(Sudoku, int);
};

#endif // SUDOKUPROP_H
