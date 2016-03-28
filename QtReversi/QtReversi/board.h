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

struct MovePos
{
    MovePos();
    MovePos(Color col, int r, int c);
    Color color;
    int row;
    int col;
};
inline MovePos::MovePos()
{
    color = kEmpty;
    row = -1;
    col = -1;
}
inline MovePos::MovePos(Color col, int r, int c)
    : color(col), row(r), col(c)
{}

inline Color opponent_of(Color color)
{
    assert(color != kEmpty);
    return color == kWhite ? kBlack : kWhite;
}

class Board
{
public:
    enum {kNRows = 8, kNCols = 8};
    Board();
    void reset();
    Color operator()(int r, int c) const;
    Color operator()(const MovePos& p) const;
    void move(Color, int r, int c);
    void move(const MovePos& p);
    MoveResult get_possible_move(Color, int& r, int& c) const;
    MoveResult get_possible_move(MovePos* p) const;
    MoveResult valid_move(Color, int r, int c) const;
    MoveResult valid_move(const MovePos& p) const;
    MovePos GetLastMove() const;
    int score(Color color) const;
private:
    Color _b[kNRows + 2][kNCols + 2];
    MovePos last_move;
    int _blacksorce;
    int _whitesorce;
};

inline bool in_board(int row, int col)
{
    return 1 <= row && row <= Board::kNRows
           && 1 <= col && col <= Board::kNCols;
}

inline bool in_board(const MovePos& p)
{
    return 1 <= p.row && p.row <= Board::kNRows
           && 1 <= p.col && p.col <= Board::kNCols;
}

inline Color Board::operator()(int r, int c) const
{
    assert(in_board(r, c));
    return _b[r][c];
}
inline Color Board::operator ()(const MovePos& p) const
{
    assert(in_board(p));
    return _b[p.row][p.col];
}

inline void Board::move(const MovePos& p)
{
    move(p.color, p.row, p.col);
}

inline int Board::score(Color color) const
{
    assert(color != kEmpty);
    return color == kWhite ? _whitesorce : _blacksorce;
}

inline MovePos Board::GetLastMove() const
{
    return last_move;
}

inline MoveResult Board::get_possible_move(MovePos* p) const
{
    return get_possible_move(p->color, p->row, p->col);
}

inline MoveResult Board::valid_move(const MovePos& p) const
{
    return valid_move(p.color, p.row, p.col);
}

#endif // BOARD_H_INCLUDED
