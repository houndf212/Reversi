#include "threadgame.h"

ThreadGame::ThreadGame(Player* black, Player* white, QObject* parent)
    : QThread(parent), Game(black, white)
{
}

void ThreadGame::run()
{
    Game::play();
    Color color = kEmpty;

    if(_board.score(kBlack) > _board.score(kWhite))
    { color = kBlack; }
    else if(_board.score(kBlack) < _board.score(kWhite))
    { color = kWhite; }

    emit sendgameover(color);
}
