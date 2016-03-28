#ifndef HUMANGUIPLAYER_H
#define HUMANGUIPLAYER_H

#include <QMutex>
#include <QWaitCondition>
#include "guiplayer.h"

class HumanGUIPlayer :  public GUIPlayer
{
    Q_OBJECT
public:
    explicit HumanGUIPlayer(Color color, QObject* parent = 0);
    virtual void get_move(const Board&, int& r, int& c);
signals:
    //走着是否合法
    void sendmoveisright(Color color, bool b);
public slots:
    virtual void setmovepos(const MovePos& p);
private:
    QMutex mutex;
    QWaitCondition waitcondition;
    MovePos movepos;
};

inline HumanGUIPlayer::HumanGUIPlayer(Color color, QObject* parent)
    : GUIPlayer(color, parent)
{
}

#endif // HUMANGUIPLAYER_H
