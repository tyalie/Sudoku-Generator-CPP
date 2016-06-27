#ifndef LASVEGASALGO_H
#define LASVEGASALGO_H

#include "Commons/common.h"

#include "Generator/GenSudoku.h"
#include "Generator/SudokuSolver.h"

#include <cstdlib>
#include <ctime>
#include <list>

inline GenSudoku LasVegasAlgo() {
    showMessage("Starting Las-Vegas-Algorithm");
    while (true) {
        std::srand(time(nullptr));

        GenSudoku terminal;
        terminal.Sudoku::setAtIndex(0, (std::rand()%9)+1 );

        for(int i=0; i<10; i++) {
            terminal.setIndex(std::rand()%81);

            std::vector<char> pos = terminal.getAvailable();
            if(pos.size()>0 && terminal.getAtIndex() == NAF)
                terminal.setAtIndex(pos[std::rand()%pos.size()]);
            else
                i--;
        }

        terminal.resetIndex();
        SudokuSolver::DFSLV(terminal, time(0), 200, std::rand()%10000 );

        if(SudokuSolver::success()) {
            return SudokuSolver::getLastField();
        } else
            showMessage("LasVegas - sudoku was not solvable in time");
    }
}

#endif // LASVEGASALGO_H
