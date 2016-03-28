#include <assert.h>
#include "board.h"

Board::Board()
{
    for (int r = 0; r != kNRows + 2; ++r)
        for (int c = 0; c != kNCols + 2; ++c)
        {
            _b[r][c] = kEmpty;
            //_b[r][c] = kBlack;
        }

    _b[kNRows / 2 + 1][kNCols / 2] = kBlack;
    _b[kNRows / 2][kNCols / 2 + 1] = kBlack;
    _b[kNRows / 2][kNCols / 2] = kWhite;
    _b[kNRows / 2 + 1][kNCols / 2 + 1] = kWhite;

    _blacksorce = 2;
    _whitesorce = 2;

}

MoveResult Board::valid_move(Color color, int r, int c) const
{
    assert(r >= 1 && r <= kNRows && c >= 1 && c <= kNCols);

    if (_b[r][c] != kEmpty)
    {
        return kUnsuccessful;
    }

    Color opponent = opponent_of(color);

    for (int dr = -1; dr != 2; ++dr)
        for (int dc = -1; dc != 2; ++dc)
            if (dr != 0 || dc != 0)
            {
                int row = r;
                int col = c;

                do
                {
                    row += dr;
                    col += dc;
                }
                while (_b[row][col] == opponent);

                if (_b[row][col] == color && (row != r + dr || col != c + dc))
                {
                    return kSuccessful;
                }
            }

    return kUnsuccessful;
}

void Board::move(Color color, int r, int c)
{
    assert(valid_move(color, r, c));

    int count = 0;

    Color opponent = opponent_of(color);

    for (int dr = -1; dr != 2; ++dr)
        for (int dc = -1; dc != 2; ++dc)
            if (dr != 0 || dc != 0)
            {
                int row = r;
                int col = c;

                do
                {
                    row += dr;
                    col += dc;
                }
                while (_b[row][col] == opponent);

                //如果这个方向上捕获了某些棋子
                //改变捕获棋子的颜色
                if (_b[row][col] == color && (row != r + dr || col != c + dc))
                {
                    for (row = r + dr, col = c + dc; _b[row][col] == opponent; row += dr, col += dc)
                    {
                        _b[row][col] = color;
                        ++count;
                    }
                }
            }



    _b[r][c] = color;

    if (color == kBlack)
    {
        _blacksorce += count + 1;
        _whitesorce -= count;
    }
    else
    {
        _whitesorce += count + 1;
        _blacksorce -= count;
    }

}

MoveResult Board::get_possible_move(Color color, int &r, int &c) const
{
    for (r = 1; r != kNRows + 1; ++r)
        for (c = 1; c != kNCols + 1; ++c)
            if (valid_move(color, r, c))
            {
                return kSuccessful;
            }

    return kUnsuccessful;
}
