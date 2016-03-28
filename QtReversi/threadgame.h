#ifndef THREADGAME_H
#define THREADGAME_H

#include <QThread>
#include "game.h"
#include "player.h"
class ThreadGame : public QThread, public Game
{
    Q_OBJECT
public:
    explicit ThreadGame(Player* black, Player* white, QObject* parent = 0);
protected:
    void run();

signals:
    void sendgameover(Color);

public slots:

};

#endif // THREADGAME_H
