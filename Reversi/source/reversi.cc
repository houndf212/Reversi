#include <iostream>
#include <stdlib.h>

#include "boardtextviewer.h"
#include "game.h"
#include "humantextplayer.h"
#include "virtualtextplayer.h"

using std::cout;
using std::cin;

int maxdepth = 6;

Player *select_player(Color color)
{
    cout << (color == kWhite ? "White: " : "Black: ")
         << "[H]uman or [C]omputer?";
    char answer;
    cin >> answer;

    if (answer == 'H' || answer == 'h')
    {
        return new HumanTextPlayer(cout, cin, color);
    }
    else
    {
        return new VirtualTextPlayer(cout, color, maxdepth);
    }
}



int main(int argc, char **argv)
{
    if (argc > 2)
    {
        cout << "please use no args!\n";
        cout << "or one number to choose difficulty! suggests 6 to 10 \n";
        return -1;
    }

    if (argc == 2)
    {
        maxdepth = atoi(argv[1]);
    }

    Player *blackplayer = select_player(kBlack);
    Player *whiteplayer = select_player(kWhite);
    BoardViewer *viewer = new BoardTextViewer(cout);
    Game game(blackplayer, whiteplayer);
    game.select_viewer(viewer);
    game.play();

    delete viewer;
    delete whiteplayer;
    delete blackplayer;
    return 0;
}
