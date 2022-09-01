#pragma once

#include "Libraries.h"

class Tile final
{
public: 
    Tile(){
        layer = 0;
        dome = false;
        white_present = false;
        black_present = false;
    };

    int layer;
    bool dome;
    bool white_present;
    bool black_present;

    friend std::ostream& operator<<(std::ostream& lhs, const Tile& rhs);
};

std::ostream& operator<<(std::ostream& lhs, const Tile& rhs)
{
    int spaces = 4;
    if(rhs.layer == 0){
        spaces = 4;
    }
    else if (rhs.layer == 1){
        lhs << "C";
        spaces = 3;
    }
    else if (rhs.layer == 2){
        lhs << "CC";
        spaces = 2;
    }
    else if (rhs.layer == 3){
        lhs << "CCC";
        spaces = 1;
    }
    
    if (rhs.dome){
        lhs << "D";
    }
    else if (rhs.white_present){
        lhs << "_O";
        spaces--;
    }
    else if (rhs.black_present){
        lhs << "_X";
        spaces--;
    }
    else{
        spaces++;
    }

    for (int i = 0 ; i < spaces; i++)
        lhs << " ";

    return lhs;
}
