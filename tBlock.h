#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"

class tBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    tBlock(int level, Grid *g);
    ~tBlock() override;

};

#endif
