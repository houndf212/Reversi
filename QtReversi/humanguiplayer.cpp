#include "humanguiplayer.h"
#include <QDebug>

void HumanGUIPlayer::get_move(const Board& board, int& r, int& c)
{
    emit sendturn(_color);

    while(true)
    {
        QMutexLocker locker(&mutex);
        waitcondition.wait(&mutex);

        if (in_board(movepos.row, movepos.col) && board.valid_move(_color, movepos.row, movepos.col) )
        {
            r = movepos.row;
            c = movepos.col;
            emit sendmoveisright(_color, true);
            emit sendmove(movepos);
            return;
        }
        else
        {
            emit sendmoveisright(_color, false);
        }
    }
}

void HumanGUIPlayer::setmovepos(const MovePos& p)
{
    assert(p.color != kEmpty && in_board(p));

    if(mutex.tryLock())
    {
        mutex.unlock();
        movepos = p;
        waitcondition.wakeAll();
    }
}
