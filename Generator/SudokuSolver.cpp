#include "SudokuSolver.h"

int SudokuSolver::cSol = 0;
GenSudoku* SudokuSolver::lastField = nullptr;

int SudokuSolver::DFS(GenSudoku &obj, bool end) {
    obj.moveNext();
    if( obj.isIndexLast() )
        return 1;

    std::list<GenSudoku> gs = obj.expand();
    if(gs.size() == 0)
        return 0;

    int sum = 0;
    for(std::list<GenSudoku>::iterator i = gs.begin(); i!=gs.end(); ++i) {
        sum += DFS(*i, end);
        if(!end && sum!=0)
            break;
    }
    return sum;
}

bool SudokuSolver::DFSLV(GenSudoku &obj, int maxSol) {
    obj.moveNext();

    if(obj.isIndexLast()) {
        if(cSol+1 == maxSol) {
            if(lastField)
                delete(lastField);
            lastField = new GenSudoku(obj);
        }
        return true;
    }

    std::list<GenSudoku> gs = obj.expand();
    if(gs.size() == 0)
        return 0;

    for(std::list<GenSudoku>::iterator i = gs.begin(); i!=gs.end(); ++i) {
        if(DFSLV(*i, maxSol))
            cSol++;
        if(cSol >= maxSol)
            return 0;
    }
    return 0;
}
