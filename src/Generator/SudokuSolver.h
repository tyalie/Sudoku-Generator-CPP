#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include "Generator/GenSudoku.h"
#include "GUI/ThreadManager.h"
#include <vector>

class SudokuSolver {
private:
    static int DFS(GenSudoku&, bool);

    int cSol;
    GenSudoku* lastField;

public:
    bool DFSLV(GenSudoku&, long, int, int);

    static int solutions(GenSudoku sudoku) {
        GenSudoku su(sudoku);
        return DFS(su, true);
    }

    static bool solvable(GenSudoku sudoku) {
        GenSudoku su(sudoku);
        su.setIndex(0);
        return DFS(su, false) > 0;
    }


    SudokuSolver() : cSol(0), lastField(nullptr) {}

    ~SudokuSolver() {
        if(lastField)
            delete lastField;
    }

    bool success() {
        return lastField;
    }

    GenSudoku getLastField() {
        if(lastField)
            return *lastField;
        else
            return GenSudoku();
    }
};

#endif // SUDOKUSOLVER_H
