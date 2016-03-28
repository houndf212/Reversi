#include <assert.h>
#include "boardtextviewer.h"
#include "board.h"

void BoardTextViewer::draw(const Board &board)
{
    assert(Board::kNCols < 10 && Board::kNRows < 27);
    int r, c;
    _output << "\n   ";

    for (c = 1; c != Board::kNCols + 1; ++c)
    {
        _output << ' ' << c;
    }


    _output << "\n  .-";

    for (r = 1; r != Board::kNCols + 1; ++r)
    {
        _output << "--";
    }

    _output << '.';

    for (r = 1; r != Board::kNCols + 1; ++r)
    {
        _output << "\n " << char('a' + r - 1) << '|';

        for (c = 1; c != Board::kNCols + 1; ++c)
            if (board(r, c) == kWhite)
            {
                _output << " o";
            }
            else if (board(r, c) == kBlack)
            {
                _output << " *";
            }
            else
            {
                _output << "  ";
            }

        _output << " |";
    }

    _output << "\n  `-";

    for (r = 1; r != Board::kNCols + 1; ++r)
    {
        _output << "--";
    }

    _output << '\'';

    _output << "\n[ Black(*): " << board.score(kBlack)
            << "   White(o): " << board.score(kWhite)
            << " ]\n\n";
}
