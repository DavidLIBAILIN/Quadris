#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"

class iBlock : public Block {

    std::vector<Block::Coord> getRotatedPieces(RotateDir rd) override;
 
public:

    iBlock(int level, Grid *g);
    ~iBlock() override;

};

#endif
