#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"

class Cell;
class GameDetails;

class TextDisplay: public Observer<Info, State> {

    std::vector<std::vector<char>> theDisplay;
    const int width;
    const int height;
    GameDetails *gdetails;
    Colour next;

public:
       
    TextDisplay(int width, int height, GameDetails *gdetails);

    // notify(whoNotified) updates the TextDisplay when it is called by a Subject, or in this 
    // case, the Cell.
    // Time: O(1)
    void notify(Subject<Info, State> &whoNotified) override;

    // << overload for TextDisplay.
    // Time: O(n), n is the width/length of the TextDisplay.
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif
