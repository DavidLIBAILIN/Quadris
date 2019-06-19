#include "iBlock.h"
#include "grid.h"


using namespace std;


iBlock::iBlock(int level, Grid *g) : Block{g, level, 'I', 0, 2} {
    // pieces spawn like this:
    // I_1 I_2 I_3 I_4

    vector<Coord> blockCoords {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
    pieces = blockCoords;
    checkPlace();
    updateCells();
}


vector<Block::Coord> iBlock::getRotatedPieces(RotateDir rd) {

    Coord c1 = pieces.at(0);
    Coord c2 = pieces.at(1);
    Coord c3 = pieces.at(2);
    Coord c4 = pieces.at(3);

    vector<Coord> rotatedPos = pieces;
    if (rd == RotateDir::CW) {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r - 3, c1.c};
            rotatedPos.at(1) = {c2.r - 2, c2.c - 1};
            rotatedPos.at(2) = {c3.r - 1, c3.c - 2};
            rotatedPos.at(3) = {c4.r, c4.c - 3};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r  + 3, c1.c};
            rotatedPos.at(1) = {c2.r + 2, c2.c + 1};
            rotatedPos.at(2) = {c3.r + 1, c3.c + 2};
            rotatedPos.at(3) = {c4.r, c4.c + 3};
        }
    }
    else {
        // CCW rotation same as CW for I block
        rotatedPos = getRotatedPieces(RotateDir::CW);
    }
    return rotatedPos;
}


iBlock::~iBlock() {}
