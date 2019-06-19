#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>
#include "cell.h"
#include "state.h"
#include "info.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
struct GameDetails;

class Grid {
    std::vector<std::vector<Cell>> the_grid;
    TextDisplay *td = nullptr;
    Observer<Info, State> *ob = nullptr; // graphicsdisplay

    int width = 11;
    int height = 18; // 15 for game area + 3 for top spawning row.
    int id_counter = 1;
    GameDetails* gdetails;

    struct PlaceBlock {
        int level_placed;
        int id;
        bool exists;
    };

    std::vector<PlaceBlock> block_vector;

public:

    // setObserver(ob) sets an observer to the Cells of the grid.
    // Time: O(1);
    void setObserver(Observer<Info, State> *ob);

    // Default constructor for Grid.
    Grid(GameDetails *gdetails);

    // Default destructor for Grid.
    ~Grid();

    // init() initalizes Grid, setting up a 2d vector and 
    // assigning appropriate neighbour cells.  It also attaches
    // any Observers to each Cell, as appropriate.
    // Time: O(wh), where w is width, h is height, of the grid.
    void init();

    // clear() clears any lingering values in the grid, and 
    // resets the grid.
    // Time: O(wh), where w and h are the widths and heights of
    //       the grid, respectively.
    void clear();

    // setCell(r, c, colour) set a cell of colour at row r,
    // column c.
    // Time: O(wh), w is width, h is height of the grid.
    void setCell(size_t r, size_t c, Colour colour);

    // placeBlock(block_coords, level_spawned) places cells in block_coords
    // into the grid, permanently, and sets the cells as
    // placed cells, allowing for line removal.
    // Time: O(wh), where w is width, h is height of the grid.
    void placeBlock(std::vector<std::vector<int>> block_coords, int level_spawned);

    // canPlace(r, c) returns whether or not a cell can
    // be added at row r, column c.
    // Time: O(1)
    bool canPlace(int r, int c);

    // dropSpecialBlock() inserts a special block for
    // level 4.  
    // Time: O(wh), where w is width, h is height.
    void dropSpecialBlock();

    // fakePlace(block_coords) stores the possible amount of points obtainable
    // the block_coords were applied into points, and the max height into height.
    // Time: O(wh)
    void fakePlace(std::vector<std::vector<int>> block_coords, int level_spawned, int& points, int& the_height, int& most_flat);

    // removeHint() removes all hint cells.
    // Time: O(wh)
    void removeHint();

    // << override for output with a reference to grid.
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);

    // << override for output with a shared pointer to grid.
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Grid> g);

};

#endif
