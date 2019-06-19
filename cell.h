#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject<Info, State>, public Observer<Info, State> {
    
    size_t x, y;
    bool left_wall, right_wall;
    const size_t board_x, board_y;
    bool removed_line;
    // getDir(i) returns the direction the coordinates from i is from the Cell.
    Direction getDir(Info i);
    // setType(type) sets the StateType of the Cell.
    void setType(StateType type);

public:
        
    Cell(size_t x, size_t y, size_t width, size_t height);
    void setCell(Colour colour);
    // notify(whoFrom) will check the value and fields of whoFrom and determine how to modify
    // this Cell as an observer.  It may then call its own neighbours to further cause changes.
    // Effects: May modify the fields of other observers.
    // Time: O(n), n is the width/length of the board.  
    void notify(Subject<Info, State> &whoFrom) override;
    // My neighbours will call this when they've changed state

    Colour getColour() const;
    // isOccupied() returns true if the Cell is occupied.
    bool isOccupied() const;
    // reset() resets some parameters of Cell.
    void reset();
    bool didScore(int id);
    void setInfoColour(Colour colour);
    ~Cell() override; 

};

#endif
