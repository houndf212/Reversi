#include "humantextplayer.h"

namespace
{
void convert(char &ch, int upper)
{
    if (ch >= 'a' && ch < 'a' + upper)
    {
        ch = ch - 'a' + 1;
    }
    else if (ch >= 'A' && ch < 'A' + upper)
    {
        ch = ch - 'A' + 1;
    }
    else if (ch >= '1' && ch < '1' + upper)
    {
        ch = ch - '1' + 1;
    }
}

bool in_board(int row, int col)
{
    return row > 0
           && row <= Board::kNRows
           && col > 0
           && col <= Board::kNCols;
}

void print_color(ostream &output, Color color)
{
    if (color == kBlack)
    {
        output << "Black(*)";
    }
    else
    {
        output << "White(o)";
    }
}
}// end of namespace

void HumanTextPlayer::get_move(const Board &board, int &r, int &c)
{
    char row, col;

    do
    {
        //board.get_possible_move(_color, r, c);
        print_color(_output, _color);
        //_output << ", enter you move (e.g: " << char('a' + r - 1) << char('1' + c - 1) << ") : ";
        _output << ", enter you move (e.g: c7) : ";
        _input >> row >> col;

        convert(row, Board::kNRows);
        convert(col, Board::kNCols);

        if (in_board(row, col) && board.valid_move(_color, row, col))
        {
            break;
        }

        board.get_possible_move(_color, r, c);
        _output << "Invalid move, Please try again.\n"
                << char('a' + r - 1) << char('1' + c - 1)
                << " is a valid example, but other moves may be better.\n";

    }
    while (true);

    r = row;
    c = col;
}

void HumanTextPlayer::skip_move(const Board &)
{
    print_color(_output, _color);
    _output << ": no valid move possible.\n";
}

void HumanTextPlayer::win()
{
    print_color(_output, _color);
    _output << " wins!\n";
}

void HumanTextPlayer::tie()
{
    if (_color == kBlack)
    {
        _output << "Game tied.\n";
    }
    else
    {
        _output << "No winner!\n";
    }
}
