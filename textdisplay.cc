#include <cassert>
#include <iomanip>

#include "textdisplay.h"
#include "subject.h"
#include "gamedetails.h"

using namespace std;

TextDisplay::TextDisplay(int width, int height, GameDetails* gdetails):
    width{width}, height{height}, gdetails{gdetails}
{
    for (int i = 0; i < (height + 3); ++i) {
        vector<char> tmp;
        for (int j = 0; j < width; ++j) {
            tmp.emplace_back(' ');
        }

        theDisplay.emplace_back(tmp);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    Info i = whoNotified.getInfo();
    char char_colour;

    //Unless we change how we process colour, this is needed.
    switch(i.colour) {
        case Colour::I:
            char_colour = 'I';
            break;
        case Colour::J:
            char_colour = 'J';
            break;
        case Colour::L:
            char_colour = 'L';
            break;
        case Colour::O:
            char_colour = 'O';
            break;
        case Colour::S:
            char_colour = 'S';
            break;
        case Colour::Z:
            char_colour = 'Z';
            break;
        case Colour::T:
            char_colour = 'T';
            break;
        case Colour::Unset:
            char_colour = ' ';
            break;
        case Colour::Hint:
            char_colour = '?';
            break;
        case Colour::Star:
            char_colour = '*';
            break;
        default:
            assert("This should not have run!  You have an undefined colour!");
    }

    theDisplay.at(i.row).at(i.col) = char_colour;

    //cout << *this;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {


    out << "Level:" << setw(7) << td.gdetails->level << endl;
    out << "Score:" << setw(7) << td.gdetails->cur_score << endl;
    out << "Hi Score:" << setw(4) << td.gdetails->high_score << endl;
    out << "-----------" << endl;

    for (int i = 0; i < td.height; ++i) {
        for (int j = 0; j < td.width; ++j) {
            out << td.theDisplay.at(i).at(j);
        }
        out << "\n";
    }

    out << "-----------" << endl;
    out << "Next:" << endl;
    
    switch(td.gdetails->next_block) {
        case 'I':
            out << endl << "IIII" << endl;
            break;
        case 'J':
            out << "J" << endl << "JJJ" << endl;
            break;
        case 'L':
            out << "  L" << endl << "LLL" << endl;
            break;
        case 'O':
            out << "OO" << endl << "OO" << endl;
            break;
        case 'S':
            out << " SS" << endl << "SS" << endl;
            break;
        case 'Z':
            out << "ZZ" << endl << " ZZ" << endl;
            break;
        case 'T':
            out << "TTT" << endl << " T"<< endl;
            break;
    }
    out << endl;
    return out;
}
