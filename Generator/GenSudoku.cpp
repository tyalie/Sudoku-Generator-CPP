#include "GenSudoku.h"

GenSudoku::GenSudoku() : index(0) {}

GenSudoku::~GenSudoku() {}

GenSudoku::GenSudoku( const GenSudoku &obj ) {
    std::memcpy(field, obj.field, sizeof(field));
    index = obj.index;
}

void GenSudoku::moveNext() {
    while(field[index] != NAF && !isIndexLast() )
        index++;
}

bool GenSudoku::isIndexLast() {
    for (size_t i = index; i < TOTAL; i++) {
        if (field[i]==NAF)
            return false;
    }
    return true;
}

bool* GenSudoku::rule1_cols(bool* possible) const {
    for (int i = 0; i < DIM_F; i++) {
        unsigned char f = field[i * DIM_F + index % DIM_F];
        if (f != NAF)
            *(possible + f-1) = false;
    }

    return possible;
}

bool* GenSudoku::rule2_rows(bool* possible) const {
    for (int i = 0; i < DIM_F; i++) {
        unsigned char f = field[i + index / DIM_F * DIM_F];
        if (f != NAF)
            *(possible + f-1) = false;
    }
    return possible;
}

bool* GenSudoku::rule3_block(bool* possible) const {
    for (int i = 0; i < DIM_F; i++) {
        unsigned char f = field[i % DIM_B + (i / DIM_B) * DIM_F
                    + (index % DIM_F) / DIM_B * DIM_B +
                    index / (DIM_F * DIM_B) * (DIM_F * DIM_B)];
        if (f != NAF)
            *(possible + f-1) = false;
    }
    return possible;
}

std::list<GenSudoku> GenSudoku::expand() {
    bool possible[9];
    std::memset(possible, true, sizeof(possible));
    std::memcpy(possible, rule1_cols(rule2_rows(rule3_block(possible))), sizeof(possible));

    std::list<GenSudoku> ret;
    for (size_t i=1;i<=9;i++) {
        if(*(possible+i-1)) {
            GenSudoku c(*this);
            c.setAtIndex(i);
            ret.push_back(c);
        }
    }
    return ret;
}
