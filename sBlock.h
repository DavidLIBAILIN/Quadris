#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"


class sBlock : public Block{

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    sBlock(int level, Grid *g);
   ~sBlock() override;

};


#endif
