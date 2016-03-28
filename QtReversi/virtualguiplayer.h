#ifndef VIRTUALGUIPLAYER_H
#define VIRTUALGUIPLAYER_H

#include <QObject>
#include "guiplayer.h"

class VirtualGUIPlayer : public GUIPlayer
{
    Q_OBJECT
public:
    static int const default_depth = 6;
    explicit VirtualGUIPlayer(Color color, int maxdepth = default_depth, QObject* parent = 0);
    virtual void get_move(const Board&, int& row, int& col);
signals:

public slots:
    virtual void setmovepos(const MovePos&) {}
private:
    const int _maxdepth;
};

inline VirtualGUIPlayer::VirtualGUIPlayer(Color color, int maxdepth, QObject* parent)
    : GUIPlayer(color, parent), _maxdepth(maxdepth)
{
}

#endif // VIRTUALGUIPLAYER_H
