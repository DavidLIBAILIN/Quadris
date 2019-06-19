#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"
#include <vector>


class Level2 : public Level{

    std::vector<char> blockTypes;
    char getNext() override; 
    Block *createBlock(Grid *g) override;
    void setRandom(bool input, std::string file = "") override; 
    
public:

    Level2(int seed = 0, char nextBlock = ' ');
    ~Level2() override;

};

#endif

