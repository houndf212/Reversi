#include <cassert>
#include "game.h"
#include "boardviewer.h"
#include "player.h"

void Game::play()
{
    assert(0 != _black && 0 != _white && 0 != _viewer);
    bool more_moves;
    _viewer->draw(_board);

    do
    {
        int r, c;
        more_moves = false;

        if (_board.get_possible_move(kBlack, r, c))
        {
            more_moves = true;
            _black->get_move(_board, r, c);
            _board.move(kBlack, r, c);
            _viewer->draw(_board);
        }
        else
        {
            _black->skip_move(_board);
        }

        if (_board.get_possible_move(kWhite, r, c))
        {
            more_moves = true;
            _white->get_move(_board, r, c);
            _board.move(kWhite, r, c);
            _viewer->draw(_board);
        }
        else
        {
            _white->skip_move(_board);
        }
    }
    while (more_moves);

    if (_board.score(kWhite) > _board.score(kBlack))
    {
        _white->win();
        _black->lose();
    }
    else if (_board.score(kBlack) > _board.score(kWhite))
    {
        _black->win();
        _white->lose();
    }
    else
    {
        _black->tie();
        _white->tie();
    }
}
