#ifndef GAME_DETAILS_H
#define GAME_DETAILS_H

#include <cmath>
#include <iostream>

using namespace std;

struct GameDetails {
    int cur_score = 0;
    int high_score = 0;
    int level = 0;
    char next_block = ' ';

    int scoreLine(int num_lines = 0) {
        //cerr << "Line score. " << endl;
        //cerr << "LINES: " << num_lines << ", LEVEL: " << level << endl;
        return (pow((num_lines + level), 2));
    }

    int scoreBlock(int level = 0) {
        //cerr << "Block score. " << endl;
        //cerr << "LEVEL: " << level << endl;
        return (pow((level + 1), 2));
    }

    void updateScore(int new_score = 0) {
        cur_score += new_score;
        if (cur_score > high_score) high_score = cur_score;
    }
};

    


#endif
