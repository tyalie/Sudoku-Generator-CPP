#ifndef SUDOKUGEN_H
#define SUDOKUGEN_H

#include "Commons/common.h"
#include "Generator/GenSudoku.h"
#include "Generator/SudokuSolver.h"

#include <bitset>
#include <cstdlib>
#include <ctime>

class SudokuGen {
private:
    static int seq1_L2RandT2B(int);
    static int seq2_WanderAlongS(int);
    static int seq3_JumpOneCell(int);
    static int seq4_RandomGlobal(std::bitset<81>);

    static bool isUnique(GenSudoku, char);
public:
    static Sudoku digHoles(GenSudoku, Level);
};

#endif // SUDOKUGEN_H
