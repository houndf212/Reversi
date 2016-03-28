#include "virtualguiplayer.h"
#include "virtualplayer.h"

void VirtualGUIPlayer::get_move(const Board& board, int& row, int& col)
{
    emit sendturn(_color);
    VirtualPlayer machine(_color, _maxdepth);
    machine.get_move(board, row, col);
    emit sendmove(MovePos(_color, row, col));
}
