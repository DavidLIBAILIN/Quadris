#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"

class lBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;

public:

    lBlock(int level, Grid *g);
    ~lBlock() override;
};

#endif
