#ifndef THREADTRIGGER_H
#define THREADTRIGGER_H

#include "Generator/GenSudoku.h"
#include "Generator/StaticGenerator.h"

struct ReturnType {
    Sudoku sudoku;
    int number;

    ReturnType() : sudoku(true), number(-1) {}

    ReturnType(Sudoku su) : sudoku(su), number(-1) {}
    ReturnType(int num) : number(num), sudoku(true) {}

    ReturnType(const ReturnType& obj) {
        sudoku = obj.sudoku;
        number = obj.number;
    }
};

inline ReturnType startGenerator(Level l) {
    showMessage("ThreadManager- Start Generator");

    Sudoku ret;
    try {
        ret = StaticGenerator(l);
    } catch (std::exception& e) {
        showMessage("ThreadManager- Generator stoped");
        return Sudoku(true);
    }
    return ReturnType(ret);
}

inline ReturnType startLasVegas() {
    showMessage("ThreadManager- Start LasVegasAlgo");

    Sudoku ret;
    try {
        ret = LasVegasAlgo();
    } catch(std::exception& e) {
        showMessage("ThreadManager- LasVegasAlgo stoped");
        return Sudoku(true);
    }
    return ReturnType(ret);
}

inline ReturnType solveSudoku(GenSudoku in) {
    showMessage("ThreadManager- Start DFSLV");

    SudokuSolver solver;

    Sudoku ret(true);
    try {
        solver.DFSLV(in, 0, -1, 1);
        if(solver.success()) {
            ret = solver.getLastField();
        } else {
            showMessage("ThreadManager- Sudoku couldn't be solved");
            QMessageBox msg;
            msg.critical(0, "Solving error", "Current Sudoku can't be solved!");
        }
    } catch(std::exception& e) {
        showMessage("ThreadManager- DFSLV aborted");
    }
    return ReturnType(ret);
}

inline ReturnType solveForAll(Sudoku in) {
    showMessage("ThreadManager- Start DFS(true)");

    int ret = -1;
    try {
        ret = SudokuSolver::solutions(GenSudoku(in));
    } catch(std::exception& e) {
        showMessage("ThreadManager- DFS(true) aborted");
        ret = -1;
    }
    return ReturnType(ret);
}

#endif // THREADTRIGGER_H
