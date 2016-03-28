#ifndef REVERSIMAINWINDOW_H
#define REVERSIMAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "qreversi.h"
#include "newgamedialog.h"

class ReversiMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ReversiMainWindow(QWidget* parent = 0);

signals:

private slots:
    void new_game();
private:
    void creatMenu();
    void creatActions();
private:
    NewGameDialog* newgamedialog;
    QReversi* reversi;

    void set_icon();
    void set_hint_size();
    QAction* newgameAction;
    QAction* exitAction;
    QMenu* gameMenu;

};

#endif // REVERSIMAINWINDOW_H
