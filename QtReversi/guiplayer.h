#ifndef GUIPLAYER_H
#define GUIPLAYER_H

#include <QObject>
#include "player.h"

class GUIPlayer : public QObject, public Player
{
    Q_OBJECT
public:
    explicit GUIPlayer(Color color, QObject* parent = 0);

signals:
    //发送轮到该玩家走棋信号，（为了绘制鼠标）
    void sendturn(Color color);
    //发送该玩家走棋信号
    void sendmove(MovePos movepos);

public slots:
    virtual void setmovepos(const MovePos&) = 0;

};

inline GUIPlayer::GUIPlayer(Color color, QObject* parent)
    : QObject(parent), Player(color)
{
}

#endif // GUIPLAYER_H
