#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include "Generator/GenSudoku.h"
#include "GUI/ThreadManager.h"
#include <vector>

class SudokuSolver {
private:
    static int DFS(GenSudoku&, bool);

    static int cSol;
    static GenSudoku* lastField;

public:
    static bool DFSLV(GenSudoku&, long, int, int);

    static int solutions(GenSudoku sudoku) {
        GenSudoku su(sudoku);
        return DFS(su, true);
    }

    static bool solvable(GenSudoku sudoku) {
        GenSudoku su(sudoku);
        su.setIndex(0);
        return DFS(su, false) > 0;
    }

    static bool success() {
        return lastField;
    }

    static GenSudoku getLastField() {
        if(lastField) {
            GenSudoku last = *lastField;
            cleanUp();
            return last;
        } else {
            return GenSudoku();
        }
    }

    static void cleanUp() {
        if(lastField) {
            delete lastField;
        }
        lastField = nullptr;
        cSol = 0;
    }
};

#endif // SUDOKUSOLVER_H
