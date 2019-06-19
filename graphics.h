#ifndef GD_H
#define GD_H

#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"

class GameDetails;

class GraphicsDisplay: public Observer<Info, State> {
    

    const int width = 900;
    const int height = 900 + 8;
    Xwindow win;
    const int grid_width = 11;
    const int grid_height = 18;
    int square_size = 50;
    GameDetails* gdetails;

    std::vector<std::vector<Colour>> gridVec;
   
    int start_x = 0;
    int start_y = 0;
    int actual_width = 0;
    int actual_height = 0;

    void drawBlock(int x, int y, int colour);
    
    public:
        // Constructor for GraphicsDisplay
        // Time: O(1)
        GraphicsDisplay(GameDetails* gdetails);

        // notify(whoNotified) updates the GraphicsDisplay when it is called by a Subject.
        // Time: O(1)
        void notify(Subject<Info, State> &whoNotified) override;

        // redraw() updates the actual window.
        // Time: O(1)
        void redraw();
};



#endif
