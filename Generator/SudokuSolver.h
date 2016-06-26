#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include "GenSudoku.h"

class SudokuSolver {
private:
    static int DFS(GenSudoku&, bool);

    static int cSol;
    static GenSudoku* lastField;

public:
    static bool DFSLV(GenSudoku&, int);

    static int solutions(GenSudoku &sudoku) {
        return DFS(sudoku, true);
    }

    static bool solvable(GenSudoku &sudoku) {
        return DFS(sudoku, false) > 0;
    }

    static Sudoku getLastField() {
        cSol = 0;
        std::cout << lastField->toString() << std::endl;

        GenSudoku last = *lastField;
        delete lastField;
        return last;
    }
};

#endif // SUDOKUSOLVER_H
