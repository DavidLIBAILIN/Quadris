#include <cassert>
#include <iostream>
#include "cell.h"

using namespace std;

Cell::Cell(size_t y, size_t x, size_t width, size_t height):
    x{x}, y{y}, left_wall{false}, right_wall{false}, board_x{width}, board_y{height}, removed_line{false}
{
    Info info;
    info.row = y;
    info.col = x;
    info.colour = Colour::Unset;
    info.id = 0;

    setInfo(info);
}

void Cell::setCell(Colour colour) { //Name
    setInfoColour(colour);   
    setType(StateType::Unset);
    notifyObservers();
}

Direction Cell::getDir(Info i) {
    if (i.row > y) {
        return Direction::Down;
    }
    else if (i.row < y) {
        return Direction::Up;
    }
    else if (i.col < x && i.row == y) {
        return Direction::Left;
    }
    else if (i.col > x && i.row == y) {
        return Direction::Right;
    }
    else {
        return Direction::Same;
    }
}



void Cell::notify(Subject<Info, State> &whoFrom) {
    Info sent_info = whoFrom.getInfo();
    State sent_state = whoFrom.getState();

    //cerr << "This is " << x << ", " << y << " notifying off of " << sent_info.col << ", " << sent_info.row << "." << endl;
 
    if ((getInfo().colour == Colour::Unset && sent_state.type != StateType::Removed) || sent_state.type == StateType::Unset || getDir(sent_info) == Direction::Up || getDir(sent_info) == Direction::Same) {
        return;
    }
    else if (sent_state.type == StateType::Removed && getState().type != StateType::Removed) {
        if (getDir(sent_info) == Direction::Down) {
            // update statetype
            setType(StateType::Removed); 
            // set temp variables to store and notify
            Colour col_tmp = getColour();
            int id_tmp = getInfo().id;
            notifyObservers();

            // swap
            Info info;
            info.row = sent_info.row;
            info.col = sent_info.col;
            info.id = id_tmp;
            info.colour = col_tmp;
            whoFrom.setInfo(info);
            //cerr << "Swapped colour at " << x << ", " << y + 1 << "." << endl;
        }
        else if (isOccupied() && getState().type == StateType::Reply) {
            //cerr << "Removing " << x << ", " << y << endl;
            setType(StateType::Removed);
            notifyObservers();
        }
    }
    else if (sent_state.type == StateType::NewPiece) {
        State tmp;
        tmp.direction = getDir(sent_info);
        if ((x <= 0 || x >= (board_x - 1)) && y == sent_info.row) {
            // We hit a wall.  Send a reply.
            tmp.type = StateType::Reply;
            //cerr << "NP Replying." << endl;
        }
        else if (y == sent_info.row) {
            // We can still go in the same direction.
            tmp.type = StateType::Relay;
            //cerr << "NP Relaying. " << endl;
        }
        setState(tmp);    
        notifyObservers();
    }
    else if (sent_state.type == StateType::Relay) {
        if (getDir(sent_info) == sent_state.direction) {
            // That means we're going in the right direction.
            State tmp;
            if ((x <= 0 || x >= (board_x - 1)) && y == sent_info.row) {
                // We hit a wall.  Send a reply.
                tmp.type = StateType::Reply;
                //cerr << "Hit wall.  Start Replying." << endl;
            }
            else if (y == sent_info.row) {
                // We can still go in the same direction.
                tmp.type = StateType::Relay;
                //cerr << "Relaying. " << endl;
            }
            tmp.direction = sent_state.direction;

            setState(tmp);    
            notifyObservers();
        }
    }
    else if (sent_state.type == StateType::Reply) {
        if ((getDir(sent_info) == Direction::Left && sent_state.direction == Direction::Right) ||
            (getDir(sent_info) == Direction::Right && sent_state.direction == Direction::Left)) { 
                // We got a reply from the opposite direction!
                if (getState().type == StateType::NewPiece) {
                    // We hit our starting piece.
                    
                    if (getDir(sent_info) == Direction::Left) left_wall = true;
                    if (getDir(sent_info) == Direction::Right) right_wall = true;
                    //cerr << "Hit NP with a reply.  LW: " << left_wall << ", RW: " << right_wall  << endl;

                    if (left_wall && right_wall) {
                        // We have to somehow drop all rows.  What I propose is a "swap".
                        // We swap this row and the one above.  That one swaps with the row above.
                        // We repeat until we cannot swap.  We then delete this row.
            
                        //cerr << "Start removing at " << x << ", " << y << endl;
                        removed_line = true;
                        setType(StateType::Removed);
                        notifyObservers();
                    }
                    return;
                }
                else if (getState().type == StateType::Reply) {
                    return;
                }
                else {
                    State tmp;
                    tmp.type = StateType::Reply;
                    tmp.direction = sent_state.direction;
                    //cerr << "Replying. " << endl;

                    setState(tmp);
                    notifyObservers();
                }
            }
    }
}


Colour Cell::getColour() const {
    return getInfo().colour;
}

bool Cell::isOccupied() const {
    return getInfo().colour != Colour::Unset;
}

void Cell::reset() {
    left_wall = false;
    right_wall = false;
    setType(StateType::Unset);
    removed_line = false;
    if (getColour() == Colour::Unset) {
        Info info;
        info.colour = Colour::Unset;
        info.row = getInfo().row;
        info.col = getInfo().col;
        info.id = 0;
        setInfo(info);
    }
}

void Cell::setType(StateType type) {
    State tmp; 
    tmp.type = type;
    tmp.direction = getState().direction;
    setState(tmp);
}

void Cell::setInfoColour(Colour colour) {
    Info info;
    info.colour = colour;
    info.row = getInfo().row;
    info.col = getInfo().col;
    info.id = getInfo().id;
    setInfo(info);
}

bool Cell::didScore(int id) {
    setType(StateType::NewPiece);
    Info info;
    info.colour = getInfo().colour;
    info.row = getInfo().row;
    info.col = getInfo().col;
    info.id = id;
    setInfo(info);

    if (x <= 0) left_wall = true;
    if (x >= board_x - 1) right_wall = true;

    //cerr << "We dropped a cell at " << x << ", " << y << endl;
    notifyObservers();

    return removed_line;
}

Cell::~Cell() {
}

