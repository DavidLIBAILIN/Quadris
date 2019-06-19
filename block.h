#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include "info.h"
#include "grid.h"
#include "state.h"

class Grid;

class Block {

    bool canMoveLeft() const;
    bool canMoveRight() const;
    bool canMoveDown() const;
    bool dropped;
    int prev_level = 0, cur_level = 0;

protected:
    struct Coord {
        int r, c;
    };

    Grid *g;
    // one of: I, J, L, O, S, Z, T.  If it isn't, it's unset (which shouldn't happen).
    char name;
    // keeps track of at which level it was dropped
    int levelDropped;
    // pieces make up the block
    std::vector<Coord> pieces;
    // keeps track of which of the possible orientations the block is in
    int orientation;
    int numOrientation;
    void wipeOldCells();
    void updateCells();
    Colour nameToColour() const;
    // throws logic error of new block can't be placed
    void checkPlace() const;
    virtual std::vector<Coord> getRotatedPieces(RotateDir rd) = 0;

public:

    Block(Grid *g, int level, char name, int orientation, int numOrientation);
    void rotate(RotateDir rd);
    void moveLeft();
    void moveRight();
    void moveDown();
    void drop();
    void hint();
    void deleteFromGrid();
    void setLevels(int old_level, int new_level);
    int getLevelDropped();
    virtual ~Block() = 0;

};

#endif
