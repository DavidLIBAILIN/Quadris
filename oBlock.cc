#include "oBlock.h"
#include "grid.h"

using namespace std;


oBlock::oBlock(int level, Grid *g) : Block{g, level, 'O', 0, 1} {
    // spawning positions:
    // O_1 O_2
    // O_3 O_4

    vector<Coord> blockCoords {{3, 0}, {3, 1}, {4, 0}, {4, 1}};
    pieces = blockCoords;
    checkPlace();
    updateCells();

}


// O block rotation doesn't do anything
vector<Block::Coord> oBlock::getRotatedPieces(RotateDir rd) {
    return pieces;
}


oBlock::~oBlock() {}
