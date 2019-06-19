#ifndef LEVEL4_H
#define LEVEL4_H

#include "level.h"
#include <vector>

class Level4 : public Level {

    std::vector<char> blockTypes;
    bool random;
    int file_pos;
    std::vector<char> block_order;
    void setFile(std::string file);
    char getNext() override;
    Block *createBlock(Grid *g) override;
    void setRandom(bool input, std::string file = "") override;

public:
    
    Level4(int seed = 0, char nextBlock = ' ');
    ~Level4() override;

};

#endif

