#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"

class jBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    jBlock(int level, Grid *g);
   ~jBlock() override;

};

#endif
