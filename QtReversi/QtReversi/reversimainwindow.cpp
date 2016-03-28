#include "reversimainwindow.h"
#include <QMenuBar>
#include <QDebug>
#include <QCloseEvent>


ReversiMainWindow::ReversiMainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    this->creatActions();
    this->creatMenu();
    this->set_icon();
    this->set_hint_size();
    reversi = new QReversi(this);
    this->setCentralWidget(reversi);
    newgamedialog = new NewGameDialog(this);
    newgamedialog->setWindowTitle("New Game");
    //new_game();
}
void ReversiMainWindow::set_icon()
{
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/ReversiIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
}

void ReversiMainWindow::set_hint_size()
{
    const int width_diff = (QReversi::koutlinealig + QReversi::kinerlinealig) * 2;
    const int height_diff = width_diff + QReversi::kscorealig;
    const int times = 1;
    const int width = width_diff + QReversi::kinner_width * times;
    const int height = height_diff + QReversi::kinner_height * times;
    this->resize(width, height);
}

void ReversiMainWindow::creatMenu()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newgameAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);
}

void ReversiMainWindow::creatActions()
{
    this->newgameAction = new QAction(tr("&NewGame"), this);
    connect(newgameAction, SIGNAL(triggered()), this, SLOT(new_game()));
    this->exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void ReversiMainWindow::new_game()
{
    if (!newgamedialog->exec())
    {
        qDebug() << " clicked cancel ";
        //return ;
    }
    else
    {
        QReversi::GameType type(QReversi::PVC);

        if(newgamedialog->rdocvc->isChecked())
        {
            type = QReversi::CVC;
        }
        else if(newgamedialog->rdopvc->isChecked())
        {
            type = QReversi::PVC;
        }
        else if(newgamedialog->rdopvp->isChecked())
        {
            type = QReversi::PVP;
        }
        else
        {
            assert(0);
        }

        int pclevel = newgamedialog->pclevel->value();
        qDebug() << int(type);
        qDebug() << pclevel;
        this->reversi->CreateNewGame(type, pclevel);
    }
}
