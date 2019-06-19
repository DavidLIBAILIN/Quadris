#include "grid.h"
#include "gamedetails.h"
#include "textdisplay.h"
#include <cassert>
#include <memory>
#include <algorithm>

using namespace std;


// See header for documentation.
Grid::Grid(GameDetails *gdetails):
    gdetails{gdetails}
{
}

// See header for documentation.
Grid::~Grid() {
    delete ob;
    delete td;
}

// See header for documentation.
void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob;
}


// See header for documentation.
void Grid::init() {
    the_grid.clear();

    for (size_t i = 0; i < static_cast<size_t>(height); ++i) {
        vector<Cell> temp;
        for (size_t j = 0; j < static_cast<size_t>(width); ++j) {
            temp.emplace_back(Cell(i, j, width, height ));
        }
        the_grid.emplace_back(temp);
    }


    if (td) delete td; //We must delete this if it is non-empty!
    td = new TextDisplay(width, height, gdetails);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Attach neighbouring cells.
            for (int k = -1; k <= 1; ++k) {
                int tmp_x = k + j;
                if (tmp_x != j && tmp_x >= 0 && tmp_x < width) {
                    the_grid.at(i).at(j).attach(&(the_grid.at(i).at(tmp_x)));
                }
            }

            int tmp_y = i - 1;
            if (tmp_y != i && tmp_y >= 0 && tmp_y < height) {
                the_grid.at(i).at(j).attach(&(the_grid.at(tmp_y).at(j)));
            }

            // Attach text display.
            if (td) the_grid.at(i).at(j).attach(td);

            // If ob exists:
            if (ob) the_grid.at(i).at(j).attach(ob);
        }
    }
}

void Grid::clear() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            setCell(i, j, Colour::Unset);
        }
    }
    init();
}

// See header for documentation.
void Grid::setCell(size_t r, size_t c, Colour colour) {
    the_grid.at(r).at(c).setCell(colour);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            the_grid.at(i).at(j).reset();
        }
    }
}

// See header for documentation.
void Grid::placeBlock(vector<vector<int>> block_coords, int level_spawned) {
    int num_lines = 0;
    int tmp_score = 0;

    PlaceBlock tmp = PlaceBlock {level_spawned, id_counter, true};
    block_vector.emplace_back(tmp);

    //We sort the vector to place the higher blocks first.
    sort(block_coords.begin(), block_coords.end(), 
            [](vector<int> a, vector<int> b) {
                return (a.at(0) < b.at(0));
            }
            );


    for (vector<int> &cur : block_coords) {
        the_grid.at(cur.at(0)).at(cur.at(1)).setCell(the_grid.at(cur.at(0)).at(cur.at(1)).getColour());

        if (the_grid.at(cur.at(0)).at(cur.at(1)).didScore(id_counter)) {
            ++num_lines;
            for (PlaceBlock &pb : block_vector) {
                if (!pb.exists) continue;
                int count = 0;
                for (int i = height - 1; i >= 0; --i) {
                    for (int j = 0; j < width; ++j) {
                        if (the_grid.at(i).at(j).getInfo().id == pb.id) {
                            ++count;
                        }
                    }
                }
                if (count == 0) {
                    tmp_score += gdetails->scoreBlock(pb.level_placed);
                    pb.exists = false;
                }
            }
        
            tmp_score += gdetails->scoreLine(num_lines);
        }


        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                the_grid.at(i).at(j).reset();
            }
        }
    }

    ++id_counter;
    gdetails->updateScore(tmp_score);
}

void Grid::removeHint() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (the_grid.at(i).at(j).getInfo().colour == Colour::Hint) {
                the_grid.at(i).at(j).setInfoColour(Colour::Unset);
                the_grid.at(i).at(j).reset();
                the_grid.at(i).at(j).notifyObservers();
            }
        }
    }
}

bool Grid::canPlace(int r, int c) {
    if (r < 0 || c < 0 || r >= height || c >= width) return false;
    return !(the_grid.at(r).at(c).isOccupied());
}

// See header for documentation.
void Grid::dropSpecialBlock() {
    int centrecol = 5;
    int row = 0;
    for (; row < height; ++row) {
        if (the_grid.at(row).at(centrecol).isOccupied()) {
            --row;
            break;
        }
    }
    setCell(row, centrecol, Colour::Star);
    vector<vector<int>> specialBlock {{row, centrecol}};
    placeBlock(specialBlock, 4);
}

// See header for documentation.
void Grid::fakePlace(vector<vector<int>> block_coords, int level_spawned, int& points, int &the_height, int &most_flat) {
    // Copied and modified version of placeBlock().

    int num_lines = 0;
    int tmp_score = 0;

    PlaceBlock tmp = PlaceBlock {level_spawned, id_counter, true};
    vector<PlaceBlock> tmp_block_vector = block_vector;
    tmp_block_vector.emplace_back(tmp);

    // First we duplicate the vector, w/o the display observers.
    vector<vector<Cell>> tmp_the_grid;
    removeHint();
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            temp.emplace_back(Cell(i, j, width, height ));
            temp.at(j).setInfo(the_grid.at(i).at(j).getInfo());
        }
        tmp_the_grid.emplace_back(temp);
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Attach neighbouring cells.
            for (int k = -1; k <= 1; ++k) {
                int tmp_x = k + j;
                if (tmp_x != j && tmp_x >= 0 && tmp_x < width) {
                    tmp_the_grid.at(i).at(j).attach(&(tmp_the_grid.at(i).at(tmp_x)));
                }
            }

            int tmp_y = i - 1;
            if (tmp_y != i && tmp_y >= 0 && tmp_y < height) {
                tmp_the_grid.at(i).at(j).attach(&(tmp_the_grid.at(tmp_y).at(j)));
            }
        }
    }

    for (vector<int> &cur : block_coords) {
        tmp_the_grid.at(cur.at(0)).at(cur.at(1)).setCell(Colour::Hint);

        if (tmp_the_grid.at(cur.at(0)).at(cur.at(1)).didScore(id_counter)) {
            ++num_lines;
            for (PlaceBlock &pb : tmp_block_vector) {
                if (!pb.exists) continue;
                int count = 0;
                for (int i = 0; i < height; ++i) {
                    for (int j = 0; j < width; ++j) {
                        if (tmp_the_grid.at(i).at(j).getInfo().id == pb.id) {
                            ++count;
                        }
                    }
                }
                if (count == 0) {
                    tmp_score += gdetails->scoreBlock(pb.level_placed);
                    pb.exists = false;
                }
            }
        }
    }

    tmp_score += gdetails->scoreLine(num_lines);
    points = tmp_score;


    for (int i = height - 1; i >= 0; --i) {
        int count = 0;
        for (int j = 0; j < width; ++j) {
            if (tmp_the_grid.at(i).at(j).isOccupied()) {
               if (i < the_height) the_height = i;
               ++count;
            }
        }
        if (count > most_flat) most_flat = count;
    }
}

// See header for documentation.
ostream &operator<<(ostream &out, const Grid &g) {
    return (out << *g.td);
}

// See header for documentation.
ostream &operator<<(ostream &out, const std::shared_ptr<Grid> g) {
    return (out << *g);
}
