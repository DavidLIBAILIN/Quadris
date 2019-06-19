#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"

class oBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    oBlock(int level, Grid *g);
   ~oBlock() override;
};

#endif
