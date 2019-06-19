#include "zBlock.h"
#include "grid.h"


using namespace std;


zBlock::zBlock(int level, Grid *g) : Block{g, level, 'Z', 0, 2} {
    // pieces spawn like this:
    // Z_1 Z_2
    //     Z_3 Z_4
    vector<Coord> blockCoords {{3, 0}, {3, 1}, {4, 1}, {4, 2}};
    pieces = blockCoords;
    checkPlace();
    updateCells();
}


vector<Block::Coord> zBlock::getRotatedPieces(RotateDir rd) {

    Coord c1 = pieces.at(0);
    Coord c3 = pieces.at(2);
    Coord c4 = pieces.at(3);

    vector<Coord> rotatedPos = pieces;

    if (rd == RotateDir::CW) {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r - 1, c1.c + 1};
            rotatedPos.at(2) = {c3.r - 1, c3.c - 1};
            rotatedPos.at(3) = {c4.r, c4.c - 2};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 1, c1.c - 1};
            rotatedPos.at(2) = {c3.r + 1, c3.c + 1};
            rotatedPos.at(3) = {c4.r, c4.c + 2};
        }
    }
    else {
        rotatedPos = getRotatedPieces(RotateDir::CW);
    }
    return rotatedPos;
}


zBlock::~zBlock() {}
