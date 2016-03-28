#ifndef HUMANTEXTPLAYER_H
#define HUMANTEXTPLAYER_H

#include <iostream>
#include "board.h"
#include "player.h"

using std::istream;
using std::ostream;

class HumanTextPlayer
        : public Player
{
public:
    HumanTextPlayer(ostream &output, istream &input, Color color);
    virtual void get_move(const Board &, int &row, int &col);
    virtual void skip_move(const Board &);
    virtual void win();
    virtual void tie();
private:
    ostream &_output;
    istream &_input;
};

inline HumanTextPlayer::HumanTextPlayer(ostream &output, istream &input, Color color)
    : Player(color), _output(output), _input(input)
{}

#endif //HUMANTEXTPLAYER_H
