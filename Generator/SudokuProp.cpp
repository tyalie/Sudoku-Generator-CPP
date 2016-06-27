#include "SudokuProp.h"

bool SudokuProp::prop1_2Digits(Sudoku &in, char d1, char d2) {
    if(d1 == d2)
        return false;

    for(int i=0;i<81;i++) {
        if(in.getAtIndex(i)==d1)
            in.setAtIndex(i, d2);
        else if(in.getAtIndex(i)==d2)
            in.setAtIndex(i, d1);
    }
    return true;
}

bool SudokuProp::prop2_2ColumnInBlock(Sudoku &in, char block, char c1, char c2) {
    if(c1 == c2)
        return false;

    for(int i=0;i<9;i++)
        std::swap(  *(in.getField()+STATIC_INDEX(block*3+c1,i)),
                    *(in.getField()+STATIC_INDEX(block*3+c2,i)) );
    return true;
}

bool SudokuProp::prop3_2ColumnOfBlock(Sudoku &in, char b1, char b2) {
    if(b1 == b2)
        return false;

    for(int i=0;i<9;i++) {
        for(int j=0;j<3;j++)
            std::swap(  *(in.getField()+STATIC_INDEX(b1*3+j,i)),
                        *(in.getField()+STATIC_INDEX(b2*3+j,i)) );
    }

    return true;
}

bool SudokuProp::prop4_GridRoll(Sudoku &in, unsigned int deg) {
    deg%=4;
    if(deg == 0)
        return false;

    Sudoku su(in);

    for(int x=0; x<9; x++) {
        for(int y=0; y<9; y++) {
            int i = -1;
            // Everybody with a beautiful, non-switch idea is welcome.
            switch (deg) {
                case 1:
                    i = STATIC_INDEX(9 - y - 1, x);
                    break;
                case 2:
                    i = STATIC_INDEX(9 - x - 1, 9 - y - 1);
                    break;
                case 3:
                    i = STATIC_INDEX(y, 9 - x - 1);
                    break;
            }
            in.setAtIndex(i, su.getAtIndex( STATIC_INDEX(x, y) ));
        }
    }
    return true;
}

#include <iostream>



Sudoku SudokuProp::propagate(Sudoku in, int steps) {
    showMessage("Started propagating with " + std::to_string(steps) + " steps");
    Sudoku ret(in);
    std::srand(std::time(0));

    while(steps>0) {
        bool get = false;
        switch(std::rand()%3 ) {
            case 0:
                get = prop2_2ColumnInBlock(ret, std::rand()%3, std::rand()%3, std::rand()%3);
                break;
            case 1:
                get = prop3_2ColumnOfBlock(ret, std::rand()%3, std::rand()%3);
                break;
            case 2:
                get = prop4_GridRoll(ret, (std::rand()%3)+1);
                break;
        }

        if(get)
            steps--;
    }

    return ret;
}
