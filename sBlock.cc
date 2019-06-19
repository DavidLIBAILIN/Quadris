#include "sBlock.h"
#include "grid.h"


using namespace std;


sBlock::sBlock(int level, Grid *g) : Block{g, level, 'S', 0, 2} {
    // pieces spawn like this:
    //     S_3 S_4
    // S_1 S_2
    
    vector<Coord> blockCoords {{4, 0}, {4, 1}, {3, 1}, {3, 2}};
    pieces = blockCoords;
    checkPlace();
    updateCells();
}


vector<Block::Coord> sBlock::getRotatedPieces(RotateDir rd) {
    Coord c1 = pieces.at(0);
    Coord c2 = pieces.at(1);
    Coord c3 = pieces.at(2);
    Coord c4 = pieces.at(3);

    vector<Coord> rotatedPos = pieces;

   if (rd == RotateDir::CW) {
       if (orientation == 0) {
            rotatedPos.at(0) = {c1.r - 2, c1.c};
            rotatedPos.at(1) = {c2.r - 1, c2.c - 1};
            rotatedPos.at(3) = {c4.r + 1, c4.c - 1};
        }
        else if (orientation == 1) {
            rotatedPos.at(0) = {c1.r + 2, c1.c};
            rotatedPos.at(1) = {c2.r + 1, c2.c + 1};
            rotatedPos.at(3) = {c4.r - 1, c4.c + 1};
        }
   }
   else {
       rotatedPos = getRotatedPieces(RotateDir::CW);
   }
   return rotatedPos;
}


sBlock::~sBlock() {}
