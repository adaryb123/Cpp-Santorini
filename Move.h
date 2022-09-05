#pragma once

#include "Libraries.h"

class Move final
{
public: 
    Move(){};

    Move(int a, int b, int c, int d, int e, int f){
        row_from = a;
        col_from = b;
        row_to = c;
        col_to = d;
        row_build = e;
        col_build = f;
    };

    int row_from;
    int col_from;
    int row_to;
    int col_to;
    int row_build;
    int col_build;

    friend std::ostream& operator<<(std::ostream& lhs, const Move& rhs);
};

std::ostream& operator<<(std::ostream& lhs, const Move& rhs)
{
    lhs << "MOVE [" << rhs.row_from+1 << "][" << static_cast<char>('A' + rhs.col_from) << "]->[" << rhs.row_to+1 << "][" << static_cast<char>('A' + rhs.col_to)
        << "] build: [" << rhs.row_build+1 << "][" << static_cast<char>('A' + rhs.col_build) <<"]\n";

    return lhs;
}