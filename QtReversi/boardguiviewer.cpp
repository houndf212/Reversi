#include "boardguiviewer.h"

BoardGUIViewer::BoardGUIViewer(QObject* parent) :
    QObject(parent)
{
}
void BoardGUIViewer::draw(const Board& board)
{
    emit sendboard(board);
}
