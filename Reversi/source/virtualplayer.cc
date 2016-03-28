#include <limits>
#include "virtualplayer.h"

void VirtualPlayer::get_move(const Board &board, int &row, int &col) const
{
    int best = std::numeric_limits<int>::min();
    int worst = std::numeric_limits<int>::max();

    row = 0;
    col = 0;

    for (int r = 1; r != Board::kNRows + 1; ++r)
        for (int c = 1; c != Board::kNCols + 1; ++c)
            if (board.valid_move(_color, r, c))
            {
                int score = eval_self(board, r, c, best, worst, 1);

                if (score > best)
                {
                    best =  score;
                    row = r;
                    col = c;
                }
            }
}

int VirtualPlayer::eval_self(const Board &board, int row, int col, int best, int worst, int d) const
{
    if (d == _maxdepth)
    {
        return value_of(board);
    }

    Board copy(board);

    if (row > 0)
    {
        copy.move(_color, row, col);
    }

    bool move_result = kUnsuccessful;

    for (int r = 1; r != Board::kNRows + 1; ++r)
        for (int c = 1; c != Board::kNCols + 1; ++c)
            if (copy.valid_move(opponent_of(_color), r, c))
            {
                move_result = kSuccessful;

                int score = eval_opponent(copy, r, c, best, worst, d + 1);

                if (score <= best)
                {
                    return score;
                }

                if (score < worst)
                {
                    worst = score;
                }
            }


    if (move_result == kSuccessful)
    {
        return worst;
    }
    else if (copy.get_possible_move(_color, row, col) == kSuccessful)
    {
        return eval_opponent(copy, 0, 0, best, worst, d + 1);
    }
    else
    {
        return eval_end_of_game(copy);
    }

}


int VirtualPlayer::eval_opponent(const Board &board, int row, int col, int best, int worst, int d) const
{
    if (d == _maxdepth)
    {
        return value_of(board);
    }

    Board copy(board);

    if (row > 0)
    {
        copy.move(opponent_of(_color), row, col);
    }

    bool move_result = kUnsuccessful;

    for (int r = 1; r != Board::kNRows + 1; ++r)
        for (int c = 1; c != Board::kNCols + 1; ++c)
            if (copy.valid_move(_color, r, c))
            {
                move_result = kSuccessful;

                int score = eval_self(copy, r, c, best, worst, d + 1);

                if (score >= worst)
                {
                    return score;
                }

                if (score > best)
                {
                    best = score;
                }
            }


    if (move_result == kSuccessful)
    {
        return best;
    }
    else if (copy.get_possible_move(opponent_of(_color), row, col) == kSuccessful)
    {
        return eval_self(copy, 0, 0, best, worst, d + 1);
    }
    else
    {
        return eval_end_of_game(copy);
    }

}

int VirtualPlayer::eval_end_of_game(const Board &board) const
{
    if (board.score(_color) > board.score(opponent_of(_color)))
    {
        return std::numeric_limits<int>::max() - 1;
    }
    else if (board.score(_color) < board.score(opponent_of(_color)))
    {
        return std::numeric_limits<int>::min() + 1;
    }
    else
    {
        return 0;
    }
}

namespace
{
int corner_value(Color player, Color corner, Color p1, Color p2, Color p3)
{
    Color opp = opponent_of(player);

    if (corner == player)
    {
        return 30;
    }

    if (corner == opp)
    {
        return -30;
    }

    int value = 0;

    if (p1 == player || p2 == player || p3 == player)
    {
        value -= 30;
    }

    if (p1 == opp || p2 == opp || p3 == opp)
    {
        value += 30;
    }

    return value;
}
}// end of namespace

int VirtualPlayer::value_of(const Board &s) const
{
    Color opp = opponent_of(_color);
    //第一个成分： 物质优势
    int value = s.score(_color) - s.score(opp);

    //第二个成分： 角落位置
    const int t = 1;
    const int l = 1;
    const int r = Board::kNCols;
    const int b = Board::kNRows;
    //左上角
    value += corner_value(_color, s(t, l),
                          s(t + 1, l), s(t, l + 1), s(t + 1, l + 1));
    //右上角
    value += corner_value(_color, s(t, r),
                          s(t + 1, r), s(t, r - 1), s(t + 1, r - 1));
    //右下角
    value += corner_value(_color, s(b, r),
                          s(b - 1, r), s(b, r - 1), s(t - 1, l - 1));
    //左下角
    value += corner_value(_color, s(b, l),
                          s(b - 1, l), s(b, l + 1), s(b - 1, l + 1));
    return value;
}
