#include "tBlock.h"
#include "grid.h"
#include <vector>

using namespace std;


tBlock::tBlock(int level, Grid *g) : Block{g, level, 'T', 0, 4} {
    // pieces spawn like this:
    // T_1 T_2 T_3
    //     T_4

    vector<Coord> blockCoords {{3, 0}, {3, 1}, {3, 2}, {4, 1}};
    pieces = blockCoords;    
    checkPlace();
    updateCells();
}


vector<Block::Coord> tBlock::getRotatedPieces(RotateDir rd) {
    Coord c1 = pieces.at(0);
    Coord c2 = pieces.at(1);
    Coord c3 = pieces.at(2);
    Coord c4 = pieces.at(3);

    vector<Coord> rotatedPos = pieces;
    if (rd == RotateDir::CW) {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r - 1, c1.c + 1};
            rotatedPos.at(2) = {c3.r + 1, c3.c - 1};
            rotatedPos.at(3) = {c4.r -1, c4.c - 1};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 2, c1.c + 1};
            rotatedPos.at(1) = {c2.r + 1, c2.c};
            rotatedPos.at(2) = {c3.r, c3.c - 1};
            rotatedPos.at(3) = {c4.r, c4.c + 1};
        }
        else if (orientation == 2) {
            rotatedPos.at(0) = {c1.r, c1.c - 2};
            rotatedPos.at(1) = {c2.r - 1, c2.c - 1};
            rotatedPos.at(2) = {c3.r - 2, c3.c};
        }
        else if (orientation == 3) {
            rotatedPos.at(0) = {c1.r - 1, c1.c};
            rotatedPos.at(1) = {c2.r, c2.c + 1};
            rotatedPos.at(2) = {c3.r + 1, c3.c + 2};
            rotatedPos.at(3) = {c4.r + 1, c4.c};
        }
    }
    else {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r + 1, c1.c};
            rotatedPos.at(1) = {c2.r, c2.c - 1};
            rotatedPos.at(2) = {c3.r - 1, c3.c - 2};
            rotatedPos.at(3) = {c4.r - 1, c4.c};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 1, c1.c - 1};
            rotatedPos.at(2) = {c3.r - 1, c3.c + 1};
            rotatedPos.at(3) = {c4.r + 1, c4.c + 1};
        }
        else if (orientation == 2) {
            rotatedPos.at(0) = {c1.r - 2, c1.c - 1};
            rotatedPos.at(1) = {c2.r - 1, c2.c};
            rotatedPos.at(2) = {c3.r, c3.c + 1};
            rotatedPos.at(3) = {c4.r, c4.c - 1};
        }
        else if (orientation == 3) {
            rotatedPos.at(0) = {c1.r, c1.c + 2};
            rotatedPos.at(1) = {c2.r + 1, c2.c + 1};
            rotatedPos.at(2) = {c3.r + 2, c3.c};
        }
    }
    return rotatedPos;
}


tBlock::~tBlock() {}
