#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"
#include <vector>

class Level3 : public Level {

    std::vector<char> blockTypes;
    bool random;
    int file_pos;
    std::vector<char> block_order;
    void setFile(std::string file);
    char getNext() override;
    Block *createBlock(Grid *g) override;
    void setRandom(bool input, std::string file = "") override;

public:
    
    Level3(int seed = 0, char nextBlock = ' ');
    ~Level3() override;

};

#endif

