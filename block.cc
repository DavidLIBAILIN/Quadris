#include "block.h"

using namespace std;

Block::Block(Grid *g, int level, char name, int orientation, int numOrientation):
    g{g}, dropped{false}, prev_level{level}, cur_level{level}, name{name},
      orientation{orientation}, numOrientation{numOrientation} {}


bool Block::canMoveLeft() const {
    for (Coord cur : pieces) {
        if (!g->canPlace(cur.r, cur.c - 1)) return false;
    }
    return true;
}


bool Block::canMoveRight() const {
    for (Coord cur : pieces) {
        if (!g->canPlace(cur.r, cur.c + 1)) return false;
    }
    return true;
}


bool Block::canMoveDown() const {
    for (Coord cur : pieces) {
        if (!g->canPlace(cur.r + 1, cur.c)) return false;
    }
    return true;
}


void Block::wipeOldCells() {
    for (Coord &cur : pieces) {
        g->setCell(cur.r, cur.c, Colour::Unset);
    }
}


Colour Block::nameToColour() const {
    switch(name) {
        case 'I':
            return Colour::I;
        case 'J':
            return Colour::J;
        case 'L':
            return Colour::L;
        case 'O':
            return Colour::O;
        case 'S':
            return Colour::S;
        case 'Z':
            return Colour::Z;
        case 'T':
            return Colour::T;
        default:
            return Colour::Unset;
    }
}


void Block::updateCells() {
    vector <vector<int>> block_coords;
    for (Coord cur : pieces) {
        g->setCell(cur.r, cur.c, nameToColour());
        if (dropped) {
            vector <int> tmp;
            tmp.emplace_back(cur.r);
            tmp.emplace_back(cur.c);
            block_coords.emplace_back(tmp);
        }
    }
    if (dropped) g->placeBlock(block_coords, prev_level);
}


void Block::moveDown() {
    wipeOldCells();
    if (canMoveDown()) {
        for (Coord &cur : pieces) { ++cur.r; }
    }
    updateCells();
}


void Block::moveLeft() {
    wipeOldCells();
    if (canMoveLeft()) {
        for (Coord &cur : pieces) { --cur.c; }
    }
    updateCells();
}


void Block::moveRight() {
    wipeOldCells();
    if (canMoveRight()) {
        for (Coord &cur : pieces) {
            ++cur.c;
        }
    }
    updateCells();
}


void Block::drop() {
    wipeOldCells();
    while (canMoveDown()) {
         for (Coord &cur : pieces) { ++cur.r; }
    }
    dropped = true;
    updateCells();
}

void Block::hint() {
    wipeOldCells();
    int best_score = 0, best_col = 0, best_num_rotations = 0, best_height = 0, best_most_flat = 0;

    std::vector<Coord> tmp_pos, final_pos;
    for (Coord &cur : pieces ) { tmp_pos.emplace_back(cur); }
    for (Coord &cur : pieces ) { final_pos.emplace_back(cur); }
    
    // First, we move it all the way back to the left.
    while (canMoveLeft()) {
        for (Coord &cur : pieces) { --cur.c; }
    }

    
    for (int j = 0; j < 4; ++j) {
        wipeOldCells();
        rotate(RotateDir::CW);
        wipeOldCells();
        bool last_right = true;
        while (last_right) {
            for (int i = 0; i < 4; ++i) {
                // 4 as there are four orientations per shape.

                rotate(RotateDir::CW);

                int tmp_height = 0;

                wipeOldCells();
                while (canMoveDown()) {
                    ++tmp_height;
                    for (Coord &cur : pieces) { ++cur.r; }
                }

                // Calculate possible score.  Copied and modified from updateCell().
                vector <vector<int>> block_coords;
                for (Coord cur : pieces) {
                    vector <int> tmp;
                    tmp.emplace_back(cur.r);
                    tmp.emplace_back(cur.c);
                    block_coords.emplace_back(tmp);
                }
                wipeOldCells();
                int tmp_score = 0, tmp_best_height = 18, tmp_most_flat = 0;
                g->fakePlace(block_coords, prev_level, tmp_score, tmp_best_height, tmp_most_flat);
                wipeOldCells();
                if (tmp_score > best_score || (tmp_score == best_score && tmp_best_height > best_height) ||
                (tmp_score == best_score && tmp_best_height == best_height && tmp_most_flat > best_most_flat)) {
                    best_height = tmp_best_height;
                    best_score = tmp_score;
                    best_most_flat = tmp_most_flat;
                    for (int k = 0; k < 4; ++k) {
                        final_pos.at(k).c = pieces.at(k).c;
                        final_pos.at(k).r = pieces.at(k).r;
                    }
                }

                // Reset everything.
                for (int i = 0; i < tmp_height; ++i) {
                    for (Coord &cur : pieces) {--cur.r;}
                }

                wipeOldCells();
            }
            for (Coord &cur : pieces) { ++cur.c; }
            for (Coord &cur : pieces) { if (cur.c >= 11) last_right = false;}
        }
        for (int k = 0; k < 4; ++k) {
            pieces.at(k).c = tmp_pos.at(k).c;
            pieces.at(k).r = tmp_pos.at(k).r;
        }
    }

    // Set cells.
    wipeOldCells();
    
    for (int k = 0; k < 4; ++k) {
        pieces.at(k).c = final_pos.at(k).c;
        pieces.at(k).r = final_pos.at(k).r;
    }

    wipeOldCells();
    while (canMoveDown()) {
        for (Coord &cur : pieces) { ++cur.r; }
    }
    
    for (Coord cur : pieces) {
        g->setCell(cur.r, cur.c, Colour::Hint);
    }

    // Completely reset.
    for (int k = 0; k < 4; ++k) {
        pieces.at(k).c = tmp_pos.at(k).c;
        pieces.at(k).r = tmp_pos.at(k).r;
    }

    updateCells();
}


void Block::checkPlace() const {
    for (Coord cur : pieces) {
        if (!g->canPlace(cur.r, cur.c)) {
            throw logic_error("no space for new block, game over");
        }
    }
}


void Block::rotate(RotateDir rd) {
    wipeOldCells();

    vector<Coord> rotatedPos = getRotatedPieces(rd);

    for (Coord cur : rotatedPos) {
        if (!g->canPlace(cur.r, cur.c)) {
            updateCells();
            return;
        }
    }
    pieces = rotatedPos;
    if (rd == RotateDir::CW) {
        orientation = (orientation + 1) % numOrientation;
    }
    else {
        if (orientation == 0) {
            orientation = numOrientation - 1;
        }
        else {
            --orientation;
        }
    }
    updateCells();
}

void Block::deleteFromGrid() {
    wipeOldCells();
}

void Block::setLevels(int old_level, int new_level) {
    prev_level = old_level;
    cur_level = new_level;
}


int Block::getLevelDropped() {
    return prev_level;
}


Block::~Block() {}
