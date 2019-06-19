#include "jBlock.h"
#include "grid.h"


using namespace std;


jBlock::jBlock(int level, Grid *g) : Block{g, level, 'J', 0, 4} {
    // pieces spawn in these specified spaces
    // J_1
    // J_2 J_3 J_4

    vector<Coord> blockCoords {{3, 0}, {4, 0}, {4, 1}, {4, 2}};
    pieces = blockCoords;
    checkPlace();
    updateCells();
}


vector<Block::Coord> jBlock::getRotatedPieces(RotateDir rd) {

    Coord c1 = pieces.at(0);
    Coord c2 = pieces.at(1);
    Coord c3 = pieces.at(2);
    Coord c4 = pieces.at(3);

    vector<Coord> rotatedPos = pieces;

    if (rd == RotateDir::CW) {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r - 1, c1.c + 1};
            rotatedPos.at(1) = {c2.r - 2, c2.c};
            rotatedPos.at(2) = {c3.r - 1, c3.c - 1};
            rotatedPos.at(3) = {c4.r, c4.c - 2};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 2, c1.c + 1};
            rotatedPos.at(1) = {c2.r + 1, c2.c + 2};
            rotatedPos.at(2) = {c3.r, c3.c + 1};
            rotatedPos.at(3) = {c4.r - 1, c4.c};
        }
        else if (orientation == 2) {
            rotatedPos.at(0) = {c1.r, c1.c - 2};
            rotatedPos.at(1) = {c2.r + 1, c2.c - 1};
            rotatedPos.at(3) = {c4.r - 1, c4.c + 1};
        }
        else if (orientation == 3) {
            rotatedPos.at(0) = {c1.r - 1, c1.c};
            rotatedPos.at(1) = {c2.r, c2.c - 1};
            rotatedPos.at(2) = {c3.r + 1, c3.c};
            rotatedPos.at(3) = {c4.r + 2, c4.c + 1};
        }
    }
    else {
        if (orientation == 0) {
            rotatedPos.at(0) = {c1.r + 1, c1.c};
            rotatedPos.at(1) = {c2.r, c2.c + 1};
            rotatedPos.at(2) = {c3.r - 1, c3.c};
            rotatedPos.at(3) = {c4.r - 2, c4.c - 1};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 1, c1.c - 1};
            rotatedPos.at(1) = {c2.r + 2, c2.c};
            rotatedPos.at(2) = {c3.r + 1, c3.c + 1};
            rotatedPos.at(3) = {c4.r, c4.c + 2};
        }
        else if (orientation == 2) {
            rotatedPos.at(0) = {c1.r - 2, c1.c - 1};
            rotatedPos.at(1) = {c2.r - 1, c2.c - 2};
            rotatedPos.at(2) = {c3.r, c3.c - 1};
            rotatedPos.at(3) = {c4.r + 1, c4.c};
        }
        else if (orientation == 3) {
            rotatedPos.at(0) = {c1.r, c1.c + 2};
            rotatedPos.at(1) = {c2.r - 1, c2.c + 1};
            rotatedPos.at(3) = {c4.r + 1, c4.c - 1};
        }
    }
    return rotatedPos;
}


jBlock::~jBlock() {}
