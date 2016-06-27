#include "SudokuGen.h"

int SudokuGen::seq1_L2RandT2B(int lastI) {
    return (lastI + 1) % 81;
}

int SudokuGen::seq2_WanderAlongS(int lastI) {
    if (lastI < 0)
            return 0;
    int i;
    if ((lastI / 9) % 2 == 0) {
        if ((lastI + 1) % 9 == 0)
            i = lastI + 9;
        else
            i = lastI + 1;
    } else {
        if (lastI % 9 == 0)
            i = lastI + 9;
        else
            i = lastI - 1;
    }

    return i % 81;
}

int SudokuGen::seq3_JumpOneCell(int lastI) {
    if (lastI < 0)
            return 0;

    int i;
    /* If somebody knows a better looking
     * solution. PLEASE implement it. I don't
     * like this decision code here.
     */
    if ((lastI / 9) % 2 == 0) {
        if ((lastI + 1) % 9 == 0)
            i = lastI + 9 - 1;
        else if ((lastI + 2) % 9 == 0)
            i = lastI + 9 + 1;
        else
            i = lastI + 2;
    } else {
        if (lastI % 9 == 1)
            i = lastI + 9 - 1;
        else if (lastI % 9 == 0)
            i = lastI + 9 + 1;
        else
            i = lastI - 2;
    }
    if (i % 81 != i)
        i = (i + 1) % 2;
    return i;
}

int SudokuGen::seq4_RandomGlobal(std::bitset<81> possible) {
    while ( !possible.all() ) {
        int i = std::rand()%81;
        if (!possible[i])
            return i;
    }
    return -1;
}

bool SudokuGen::isUnique(GenSudoku tmp,char orig) {
    std::list<GenSudoku> nodes = tmp.expand();
    for( std::list<GenSudoku>::iterator i = nodes.begin(); i!=nodes.end(); i++ ) {
        if(i->Sudoku::getAtIndex( tmp.getIndex() ) != orig) {
            if(SudokuSolver::solvable(*i))
                return false;
        }
    }
    return true;
}

Sudoku SudokuGen::digHoles(GenSudoku in, Level level) {
    showMessage("Starting Digging Holes");

    std::srand(std::time(0));
    std::bitset<81> possible;

    Info info = getInfo(level);
    int minBound = std::rand()%(info.maxTotalGiven-info.minTotalGiven) + info.minTotalGiven;

    int i = -1;
    while(!possible.all()) {
        switch(level) {
            case ExtremlyEasy:
            case Easy:
                i = seq4_RandomGlobal(possible); break;
            case Medium:
                i = seq3_JumpOneCell(i); break;
            case Hard:
                i = seq2_WanderAlongS(i); break;
            case Evil:
                i = seq1_L2RandT2B(i); break;
        }

        GenSudoku tmp = in.digClone(i);
        if( isUnique(tmp, in.Sudoku::getAtIndex(i) ) && tmp.getTotalCells() >= info.minTotalGiven
                && tmp.getLowerBoundRC() >= info.minGivenRC)
            in = tmp;
        possible[i] = true;
    }
    showMessage("Digging holes at level "+info.name + " successfull with: TC-"+
            std::to_string(in.getTotalCells())+" RC-"+std::to_string(in.getLowerBoundRC()));

    return in;
}
