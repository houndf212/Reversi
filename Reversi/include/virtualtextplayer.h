#ifndef VIRTUALTEXTPLAYER_H
#define VIRTUALTEXTPLAYER_H

#include <iostream>
#include "player.h"
#include "board.h"

class VirtualTextPlayer
    : public Player
{
public:
    VirtualTextPlayer(std::ostream &output, Color color, int maxdepth = default_depth);
    virtual ~VirtualTextPlayer() {}
    virtual void get_move(const Board &, int &row, int &col);
    virtual void skip_move(const Board &);
    virtual void win();
    virtual void tie();
private:
    static int const default_depth;
    std::ostream &_output;
    const int _maxdepth;
};

inline VirtualTextPlayer::VirtualTextPlayer(std::ostream &output, Color color, int maxdepth)
    : Player(color), _output(output), _maxdepth(maxdepth)
{
}
#endif //VIRTUALTEXTPLAYER_H
