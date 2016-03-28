#ifndef GAME_H
#define GAME_H

#include "board.h"

class BoardViewer;
class Player;

class Game
{
public:
    Game(Player* black, Player* white);
    void select_viewer(BoardViewer* viewer);
    void play();
    void reset(Player* black, Player* white);
protected:
    Player* _black;
    Player* _white;
    Board _board;
    BoardViewer* _viewer;
};

inline Game::Game(Player* black, Player* white)
    : _black(black), _white(white), _viewer(0)
{
}
inline void Game::select_viewer(BoardViewer* viewer)
{
    _viewer = viewer;
}
inline void Game::reset(Player* black, Player* white)
{
    _board.reset();
    _black = black;
    _white = white;
}
#endif //GAME_H
