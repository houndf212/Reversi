#ifndef GAME_H
#define GAME_H

#include "board.h"

class BoardViewer;
class Player;

class Game
{
public:
    Game(Player *black, Player *white);
    void select_viewer(BoardViewer *viewer);
    void play();
private:
    Player *_black;
    Player *_white;
    Board _board;
    BoardViewer *_viewer;
};

inline Game::Game(Player *black, Player *white)
    : _black(black), _white(white), _viewer(0)
{
}
inline void Game::select_viewer(BoardViewer *viewer)
{
    _viewer = viewer;
}
#endif //GAME_H
