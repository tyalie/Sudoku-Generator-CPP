#ifndef STATICGENERATOR_H
#define STATICGENERATOR_H

#include "Commons/common.h"
#include "Generator/GenSudoku.h"
#include "Generator/LasVegasAlgo.h"
#include "Generator/SudokuGen.h"
#include "Generator/SudokuProp.h"

inline Sudoku StaticGenerator(Level l) {
    while(true) {
        Sudoku genSu = LasVegasAlgo();
        genSu = SudokuGen::digHoles(static_cast<GenSudoku>(genSu), l);

        if( static_cast<GenSudoku>(genSu).getTotalCells() <= getInfo(l).maxTotalGiven ) {
            genSu = SudokuProp::propagate(genSu, 300);
            return genSu;
        }
    }
}

#endif
