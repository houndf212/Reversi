#include "virtualtextplayer.h"
#include "board.h"
#include "virtualplayer.h"
namespace
{
void print_color(std::ostream &output, Color color)
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

int const VirtualTextPlayer::default_depth = 6;

void VirtualTextPlayer::get_move(const Board &board, int &row, int &col)
{
    VirtualPlayer machine(_color, _maxdepth);
    machine.get_move(board, row, col);
    print_color(_output, _color);
    _output << " plays ["
            << char('a' + row - 1) << char('1' + col - 1) << "]\n";
}
void VirtualTextPlayer::skip_move(const Board &)
{
    print_color(_output, _color);
    _output << ":no valid move possible.\n";
}

void VirtualTextPlayer::win()
{
    print_color(_output, _color);
    _output << " wins!\n";
}

void VirtualTextPlayer::tie()
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
