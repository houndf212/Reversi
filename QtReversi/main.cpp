#include <QApplication>
#include "reversimainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    ReversiMainWindow mainwin;
    mainwin.resize(600,600);
    mainwin.show();
    return a.exec();
}
