#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"

class zBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    zBlock(int level, Grid *g);
   ~zBlock() override;

};

#endif
