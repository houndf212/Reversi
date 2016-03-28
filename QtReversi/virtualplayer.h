#ifndef WIRTUALPLAYER_H
#define WIRTUALPLAYER_H

#include "board.h"

class VirtualPlayer
{
public:
    VirtualPlayer(Color color, int maxdepth = 6);
    void get_move(const Board&, int& row, int& col) const;
private:
    int eval_self(const Board&, int r, int c, int best, int worst, int depth) const;
    int eval_opponent(const Board&, int r, int c, int best, int worst, int depth) const;
    int eval_end_of_game(const Board&) const;
    int value_of(const Board&) const;
    const Color _color;
    const int _maxdepth;
};

inline VirtualPlayer::VirtualPlayer(Color color, int maxdepth)
    : _color(color), _maxdepth(maxdepth)
{
}

#endif //WIRTUALPLAYER_H
