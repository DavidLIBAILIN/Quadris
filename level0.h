#ifndef LEVEL0_H
#define LEVEL0_H

#include <vector>
#include "level.h"

class Level0 : public Level{
    // position in vector of next block
    int file_pos;
    std::vector<char> block_order;
    char getNext() override;
    Block* createBlock(Grid *) override;
    void setRandom(bool input, std::string file = "") override;
 
public:

    Level0(std::string file, char nextBlock);
    ~Level0() override;

};

#endif
