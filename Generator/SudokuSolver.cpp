#include "SudokuSolver.h"

int SudokuSolver::cSol = 0;
GenSudoku* SudokuSolver::lastField = nullptr;

int SudokuSolver::DFS(GenSudoku &obj, bool end) {
    obj.moveNext();
    if( obj.isIndexLast() )
        return 1;



    int sum = 0;

    std::vector<char> v = obj.getAvailable();
    if(v.size() == 0)
        return 0;

    for(char item : v) {
        obj.setAtIndex(item);
        int ret = DFS(obj, end);
        if(ret>0) {
            if(!end)
                return 1;
            else
                sum+=ret;
        }
        obj.setAtIndex(0);
        obj.moveNext();
    }
        /*std::list<GenSudoku> gs = obj.expand();
        if(gs.size() == 0)
            return 0;


        for(std::list<GenSudoku>::iterator i = gs.begin(); i!=gs.end(); ++i) {
            sum += DFS(*i, end);
            if(!end && sum!=0)
                break;
        }*/
    return sum;
}

bool SudokuSolver::DFSLV(GenSudoku &obj,long start, int max,  int maxSol) {
    obj.moveNext();

    if( (time(0)-start)>max && max>0)
        return false;

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
        if(DFSLV(*i,start, max, maxSol))
            cSol++;
        if(cSol >= maxSol)
            return 0;
    }
    return 0;
}
