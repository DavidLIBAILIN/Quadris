#ifndef STATE_H
#define STATE_H

enum class StateType { NewPiece, Relay, Reply, Removed, Unset}; 
enum class Colour { I, J, L, O, S, Z, T, Unset, Hint, Star};
enum class Direction { Left, Right, Up, Down, Same };
enum class RotateDir { CW, CCW };

struct State {
    StateType type;  
    Direction direction;
    int row;
};


#endif
