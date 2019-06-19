#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <ctime>
#include <fstream>
#include "grid.h"
#include "level.h"
#include "graphics.h"
#include "gamedetails.h"

#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;


const int minLevel = 0;
const int maxLevel = 4;


Level *createLevel(int level, int seed, char nextBlock, string file = "sequence.txt") {
    if (level == 0) return new Level0{file, nextBlock};
    else if (level == 1) return new Level1{seed, nextBlock};
    else if (level == 2) return new Level2{seed, nextBlock};
    else if (level == 3) return new Level3{seed, nextBlock};
    else if (level == 4) return new Level4{seed, nextBlock};
    return nullptr;
}


// returns full command from "cmd" root
string getCommand(string cmd, const vector<string> &commands) {
    int numAppearances = 0;
    string fullcmd;
    for (string command : commands) {
        if (cmd == command.substr(0, cmd.length())) {
            numAppearances++;
            fullcmd = command;
        }
    }
    // if there was more than one appearance, than it is
    // ambiguous. If less than one, then invalid command.
    if (numAppearances == 1) {
        return fullcmd;
    }
    return "";
}


void playGame(int argc, char *argv[]) {
    int level = 0, old_level = 0;
    int old_score = 0;
    int seed = time(NULL);
    string source_file = "sequence.txt";
    auto *gdetails = new GameDetails{0,0,0, ' '};
    bool make_display = true;

    const vector<string> commands{"left", "right", "down", "clockwise", "counterclockwise",
        "drop", "levelup", "leveldown", "norandom", "random", "sequence", "restart", "hint",
	    "I", "S", "Z", "T", "J", "L", "O", "quit"};

	//Get the options from the command line.
	for (int i = 1; i < argc; ++i) {
		string str = argv[i];
		if (str == "-text") {
		    make_display = false;
        }
        else if (str == "-seed") {
			seed = stoi(argv[i + 1]);
		}
        else if (str == "-scriptfile") {
            source_file = argv[i+1];
		}
        else if (str == "-startlevel") {
			gdetails->level = old_level = level = stoi(argv[i + 1]);
		}
	}

    // RNG
    srand(seed);

    cin.exceptions(ios::eofbit|ios::failbit);

    GraphicsDisplay *gd = nullptr;
    Grid *g = new Grid(gdetails);
    if (make_display) {
            gd = new GraphicsDisplay(gdetails);
            g->setObserver(gd);
    }
    g->init();

    string cmd;
    Level *l = createLevel(level, seed, gdetails->next_block, source_file);
    Block *b = nullptr;

    try {
        // used for level 4 special block generation
        int blocksSinceLastClear = 0;
        l->getNextNV();
        b = l->createBlockNV(g);
        gdetails->next_block = l->returnNext();
        // Initial draw.
        cout << *g;
        if (gd) gd->redraw();

        bool readingFromFile = false;
        ifstream file{""};

        while (true) {
            if (b == nullptr) break;
            if (readingFromFile) {
                if (!file.eof()) {
                    file >> cmd;
                }
                else {
                    readingFromFile = false;
                    cin >> cmd;
                }
            }
            else {
                cin >> cmd;
            }
            int multiplier = -1;
            if (cmd[0] >= '0' && cmd[0] <= '9') {
                stringstream ss{cmd};
                ss >> multiplier;
                // remove numbers from front of command
                cmd.erase(0, to_string(multiplier).length());
            }
            // calculate full command, if its a short form
            string fullcmd = getCommand(cmd, commands);
            if (fullcmd == "quit") return;
            // if there was no multiplier, do it once
            if (multiplier == -1) multiplier = 1;

            // We must remove hint blocks.
            g->removeHint();

            for (int i = 0; i < multiplier; ++i) {
                // short cut not recognized
                if (fullcmd == "") continue;
                else if (fullcmd == "levelup") {
                    if (level < maxLevel) {
                        ++level;
                        delete l;
                        l = createLevel(level, seed, gdetails->next_block);
                        ++(gdetails->level);
                    }
                }
                else if (fullcmd == "leveldown") {
                    if (level > minLevel) {
                        --level;
                        delete l;
                        l = createLevel(level, seed, gdetails->next_block);
                        --(gdetails->level);
                    }
                }
                else if (fullcmd == "left") {
                    b->moveLeft();
                }
                else if (fullcmd == "right") {
                    b->moveRight();
                }
                else if (fullcmd == "down") {
                    b->moveDown();
                }
                else if (fullcmd == "drop") {
                    b->drop();
                    if (level == 4 && old_score == gdetails->cur_score) {
                        ++blocksSinceLastClear;
                        if (blocksSinceLastClear >= 5) {
                            // drops the 1x1 * block
                            g->dropSpecialBlock();
                            blocksSinceLastClear = 0;
                            old_score = gdetails->cur_score;
                        }
                    }
                    else {
                        old_score = gdetails->cur_score;
                        blocksSinceLastClear = 0;
                    }
                    delete b;
                    // create throws logic error if a new block
                    // cant be placed on the board
                    try {
                        b = l->createBlockNV(g);
                        gdetails->next_block = l->returnNext();
                        b->setLevels(old_level, gdetails->level);
                        old_level = gdetails->level;
                    } catch (logic_error &le) {
                        cout << *g;
                        if (gd) gd->redraw();
                        cout << "Game Over! Your score was ";
                        cout << gdetails->cur_score << endl << endl;
                        if (l) delete l;
                        g->clear();
                        old_level = gdetails->level = 0;
                        gdetails->next_block = ' ';
                        gdetails->cur_score = 0;
                        l = createLevel(level, seed, gdetails->next_block);
                        l->getNextNV();
                        b = l->createBlockNV(g);
                        gdetails->next_block = l->returnNext();
                    }
                }
                else if (fullcmd == "clockwise") {
                    b->rotate(RotateDir::CW);
                }
                else if (fullcmd == "counterclockwise") {
                    b->rotate(RotateDir::CCW);
                }
                else if (fullcmd == "I" || fullcmd == "J" || fullcmd == "L" ||
                         fullcmd == "O" || fullcmd == "S" || fullcmd == "T" ||
                         fullcmd == "Z") {
                    b->deleteFromGrid();
                    delete b;
                    b = l->charToBlock(level, fullcmd[0], g);
                    b->setLevels(old_level, gdetails->level);
                }
            }
            // these commands outside the loop do not work with number multiplier
            if (b->getLevelDropped() == 3) {
                if (fullcmd == "clockwise" || fullcmd == "counterclockwise" ||
                    fullcmd == "down" || fullcmd == "right" || fullcmd == "left") {
                    b->moveDown();
                }
            }
            if (fullcmd == "restart") {
                if (l) delete l;
                if (b) delete b;
                g->clear();
                old_level = level = gdetails->level = 0;
                gdetails->next_block = ' ';
                gdetails->cur_score = 0;
                l = createLevel(level, seed, gdetails->next_block);
                l->getNextNV();
                b = l->createBlockNV(g);
                gdetails->next_block = l->returnNext();
            }
            else if (fullcmd == "hint") {
                b->hint();
            }
            else if (fullcmd == "sequence") {
                string filename;
                if (readingFromFile) {
                    file >> filename;
                }
                else {
                    cin >> filename;
                }
                file.close();
                file.open(filename);

                readingFromFile = true;
            }
            else if (fullcmd == "norandom") {
                string filename;
                if (readingFromFile) {
                    file >> filename;
                }
                else {
                    cin >> filename;
                }
                l->setRandomNV(false, filename);
            }
            else if (fullcmd == "random") {
                l->setRandomNV(true);
            }

            //Redisplay.
	        cout << endl;
            cout << *g;
            if (gd) gd->redraw();
        }
    }
    catch (ios::failure &) {}
    if (l) delete l;
    if (b) delete b;
    delete g;
    delete gdetails;
}


int main(int argc, char *argv[]) {
    playGame(argc, argv);
}
