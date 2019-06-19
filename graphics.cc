#include <string>
#include "graphics.h"
#include "subject.h"
#include "gamedetails.h"

using namespace std;

// See header for documentation.
GraphicsDisplay::GraphicsDisplay(GameDetails* gdetails) :
    win{width, height}, gdetails{gdetails}
{

    // Initalize vector.
    for (int i = 0; i < grid_height; ++i) {
        vector<Colour> tmp;
        for (int j = 0; j < grid_width; ++j) {
            tmp.emplace_back(Colour::Unset);
        }
        gridVec.emplace_back(tmp);
    }


    win.fillRectangle(0, 0, width, height, 18);

    actual_width = square_size * grid_width;
    actual_height = square_size * grid_height;
    start_x = width - actual_width;
    start_y = 4;

    win.fillRectangle(start_x - 4, start_y - 4, actual_width + 8, actual_height + 8, 18);
    win.fillRectangle(start_x, start_y, actual_width, actual_height, 1);
}


// See header for documentation.
void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
    //We want to update our grid display!
    Info i = whoNotified.getInfo();
    gridVec.at(i.row).at(i.col) = i.colour; 
}

void GraphicsDisplay::drawBlock(int x, int y, int colour) {
    if (colour == 10 || colour == 1) {
        win.fillRectangle(x, y, square_size, square_size, colour); 
    }
    else {
        win.fillRectangle(x + 1, y + 1, square_size - 2, square_size - 2, colour); 
    }
}


void GraphicsDisplay::redraw() {
    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {
            int colour = (j % 2) ? 10 : 1;
            drawBlock(start_x + j * square_size, start_y + i * square_size, colour);
            switch(gridVec.at(i).at(j)) {
                case Colour::I:
                    colour = 2;
                    break;
                case Colour::J:
                    colour = 7;
                    break;
                case Colour::L:
                    colour = 6;
                    break;
                case Colour::O:
                    colour = 5;
                    break;
                case Colour::S:
                    colour = 4;
                    break;
                case Colour::Z:
                    colour = 3;
                    break;
                case Colour::T:
                    colour = 8;
                    break;
                case Colour::Unset:
                    colour = (j % 2) ? 10 : 1;
                    break;
                case Colour::Hint:
                    colour = 0;
                    break;
                case Colour::Star:
                    colour = 9;
                    break;
            }
            drawBlock(start_x + j * square_size, start_y + i * square_size, colour);
        }
    }

    win.fillRectangle(0, 0, width - actual_width, actual_height, 18);

    win.drawBigString(10, 50, "Level: " + to_string(gdetails->level), 1);
    win.drawBigString(10, 125, "Score: " + to_string(gdetails->cur_score), 1);
    win.drawBigString(10, 200, "Hi Score: " + to_string(gdetails->high_score), 1);
    win.drawBigString(10, 275, "Next Block:" , 1);

    int block_height = 300;
    switch(gdetails->next_block) {
        case 'I':
            drawBlock(10, block_height, 2);
            drawBlock(10 + square_size, block_height, 2);
            drawBlock(10 + 2 * square_size, block_height, 2);
            drawBlock(10 + 3 * square_size, block_height, 2);
            break;
        case 'J':
            drawBlock(10, block_height, 7);
            drawBlock(10, block_height + square_size, 7);
            drawBlock(10 + 1 * square_size, block_height + square_size, 7);
            drawBlock(10 + 2 * square_size, block_height + square_size, 7);
            break;
        case 'L':
            drawBlock(10 + 2 * square_size, block_height, 6);
            drawBlock(10 + 0 * square_size, block_height + square_size, 6);
            drawBlock(10 + 1 * square_size, block_height + square_size, 6);
            drawBlock(10 + 2 * square_size, block_height + square_size, 6);
            break;
        case 'O':
            drawBlock(10, block_height, 5);
            drawBlock(10 + square_size, block_height, 5);
            drawBlock(10, block_height + square_size, 5);
            drawBlock(10 + square_size, block_height + square_size, 5);
            break;
        case 'S':
            drawBlock(10 + square_size, block_height, 4);
            drawBlock(10 + 2 * square_size, block_height, 4);
            drawBlock(10 + 0 * square_size, block_height + square_size, 4);
            drawBlock(10 + square_size, block_height + square_size, 4);
            break;
        case 'Z':
            drawBlock(10, block_height, 3);
            drawBlock(10 + square_size, block_height, 3);
            drawBlock(10 + 1 * square_size, block_height + square_size, 3);
            drawBlock(10 + 2 * square_size, block_height + square_size, 3);
            break;
        case 'T':
            drawBlock(10, block_height, 8);
            drawBlock(10 + square_size, block_height, 8);
            drawBlock(10 + 2 * square_size, block_height, 8);
            drawBlock(10 + square_size, block_height + square_size, 8);
            break;
    }  
}
