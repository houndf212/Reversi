#ifndef BOARD_H
#define BOARD_H

#include <assert.h>

enum MoveResult
{
    kUnsuccessful = 0,
    kSuccessful
};

enum Color
{
    kEmpty = 0,
    kWhite,
    kBlack
};

inline Color opponent_of(Color color)
{
    assert((color == kWhite) || (color == kBlack));
    return color == kWhite ? kBlack : kWhite;
}

class Board
{
public:
    enum {kNRows = 8, kNCols = 8};
    Board();
    Color operator()(int r, int c) const;
    void move(Color, int r, int c);
    MoveResult get_possible_move(Color, int &r, int &c) const;
    MoveResult valid_move(Color, int r, int c) const;
    int score(Color color) const;
private:
    Color _b[kNRows + 2][kNCols + 2];
    int _blacksorce;
    int _whitesorce;
};

inline Color Board::operator()(int r, int c) const
{
    return _b[r][c];
}

inline int Board::score(Color color) const
{
    return color == kWhite ? _whitesorce : _blacksorce;
}

#endif // BOARD_H_INCLUDED
