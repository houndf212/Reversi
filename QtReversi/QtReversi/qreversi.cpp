#include <QtGui>
#include <QBrush>
#include <QPointF>
#include <QDebug>
#include <QFont>
#include <QPixmap>

#include "qreversi.h"
#include "humanguiplayer.h"
#include "virtualguiplayer.h"
#include "boardguiviewer.h"
#include "newgamedialog.h"

QReversi::QReversi(QWidget* parent)
    : QWidget(parent)
{
    init_cursor();
    gameover = false;
    thisturncolor = kEmpty;
    winner = kEmpty;
    clickpos.setX(-1);
    clickpos.setY(-1);
    //for connect
    qRegisterMetaType<MovePos>("MovePos");
    qRegisterMetaType<Board>("Board");
    qRegisterMetaType<Color>("Color");
    viewer = new BoardGUIViewer(this);
    connect(viewer, SIGNAL(sendboard(Board)), this, SLOT(setboard(Board)));
    player_black = player_white = 0;
    game = new ThreadGame(player_black, player_white, this);
    game->select_viewer(viewer);
    connect(game, SIGNAL(sendgameover(Color)), this, SLOT(setgameover(Color)));
}

void QReversi::CreateNewGame(QReversi::GameType type, int pclevel)
{
    killandwaitgamethread();
    delete player_white;
    delete player_black;

    switch(type)
    {
    case QReversi::PVP:
        player_black = new HumanGUIPlayer(kBlack, this);
        connect(this, SIGNAL(sendmovepos(const MovePos&)), player_black, SLOT(setmovepos(const MovePos&)));
        connect(player_black, SIGNAL(sendturn(Color)), this, SLOT(setthisturncolor(Color)));
        player_white = new HumanGUIPlayer(kWhite, this);
        connect(this, SIGNAL(sendmovepos(const MovePos&)), player_white, SLOT(setmovepos(const MovePos&)));
        connect(player_white, SIGNAL(sendturn(Color)), this, SLOT(setthisturncolor(Color)));
        break;

    case QReversi::CVC:
        player_black = new VirtualGUIPlayer(kBlack, pclevel, this);
        connect(player_black, SIGNAL(sendturn(Color)), this, SLOT(setthisturncolor(Color)));
        player_white = new VirtualGUIPlayer(kWhite, pclevel, this);
        connect(player_white, SIGNAL(sendturn(Color)), this, SLOT(setthisturncolor(Color)));
        break;

    case QReversi::PVC:
        player_black = new HumanGUIPlayer(kBlack, this);
        connect(this, SIGNAL(sendmovepos(const MovePos&)), player_black, SLOT(setmovepos(const MovePos&)));
        connect(player_black, SIGNAL(sendturn(Color)), this, SLOT(setthisturncolor(Color)));
        player_white = new VirtualGUIPlayer(kWhite, pclevel, this);
        break;

    default:
        assert(0);
    }

    game->reset(player_black, player_white);
    this->resetgame();
    game->start();
}
void QReversi::killandwaitgamethread()
{
    if(this->game->isRunning())
    {
        game->terminate();
        game->wait();
        assert(game->isFinished());
        this->gameover = true;
        winner = kEmpty;
    }
}
QReversi::~QReversi()
{
    killandwaitgamethread();
    qDebug() << "QReversi::~QReversi()";
}

QRect QReversi::get_out_rect() const
{
    return QRect(QReversi::koutlinealig,
                 QReversi::koutlinealig + QReversi::kscorealig,
                 width() - 2 * QReversi::koutlinealig,
                 height() - 2 * QReversi::koutlinealig - QReversi::kscorealig);
}

QRect QReversi::get_view_rect() const
{
    return get_out_rect().adjusted(QReversi::kinerlinealig,
                                   QReversi::kinerlinealig,
                                   -QReversi::kinerlinealig,
                                   -QReversi::kinerlinealig);
}

void QReversi::get_board_matrix_lines()
{
    {
        const int ysize = get_y_size();

        for (int i = 0; i != Board::kNRows + 1; ++i)
        {
            int y = i * ysize;
            board_row_lines[i].setLine(0, y, kinner_width, y);
        }
    }
    {
        const int xsize = get_x_size();

        for (int i = 0; i != Board::kNCols + 1; ++i)
        {
            int x = i * xsize;
            board_col_lines[i].setLine(x, 0, x, kinner_height);
        }
    }
}

void QReversi::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //不能旋转
    painter.setWorldMatrixEnabled(false);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //绘制分数
    draw_score_and_winner(&painter);
    //绘制外边框
    painter.drawRect(get_out_rect());
    //绘制坐标
    draw_board_coordinate(&painter);
    painter.setViewport(get_view_rect());
    painter.setWindow(0, 0, kinner_width, kinner_height);
    //绘制棋盘布线
    draw_board_matrix(&painter);
    draw_chesses(&painter);
    draw_lastmove(&painter);
    //保存当前变换
    curtransform = painter.combinedTransform().inverted();
}

void QReversi::mouseReleaseEvent(QMouseEvent* e)
{
    if (!(e->button() & Qt::LeftButton))
    { return; }

    clickpos = e->pos();
    const QPoint p = trans_point(clickpos);
    get_row_col(p, &click_row, &click_col);
    qDebug() << "row " << click_row;
    qDebug() << "col " << click_col;
    const MovePos pp(thisturncolor, click_row + 1, click_col + 1);
    sendmovepos(pp);
}

void QReversi::draw_board_matrix(QPainter* painter)
{
    get_board_matrix_lines();
    painter->drawLines(this->board_row_lines, Board::kNRows + 1);
    painter->drawLines(this->board_col_lines, Board::kNCols + 1);
}

void QReversi::draw_chesses(QPainter* painter)
{
    for (int r = 1; r != Board::kNCols + 1; ++r)
    {
        for (int c = 1; c != Board::kNCols + 1; ++c)
            if (curboard(r, c) == kWhite)
            {
                this->draw_circle(painter, r - 1, c - 1, kWhite);
            }
            else if (curboard(r, c) == kBlack)
            {
                this->draw_circle(painter, r - 1, c - 1, kBlack);
            }
    }
}

void QReversi::draw_circle(QPainter* painter, int row, int col, Color color)
{
    const QPoint center = get_rect_center(row, col);

    if(color == kWhite)
    {
        painter->setBrush(QBrush(Qt::white));
    }
    else
    {
        painter->setBrush(QBrush(Qt::black));
    }

    painter->drawEllipse(center, kradius, kradius);
}

void QReversi::draw_lastmove(QPainter* painter)
{
    MovePos lastpos = curboard.GetLastMove();

    if (lastpos.color == kEmpty)
    { return; }

    lastpos.row -= 1;
    lastpos.col -= 1;
    const Color color = lastpos.color;
    QPoint center = get_rect_center(lastpos.row, lastpos.col);
    QLine line1(center.x() - kradius / 2, center.y(), center.x() + kradius / 2, center.y());
    QLine line2(center.x(), center.y() - kradius / 2, center.x(), center.y() + kradius / 2);
    QColor qcolor;

    if(color == kBlack)
    {
        qcolor = Qt::white;
    }
    else
    {
        qcolor = Qt::black;
    }

    QPen pen(qcolor);
    const int xsize = get_x_size();
    pen.setWidth(xsize / 10);
    painter->setPen(pen);
    painter->drawLine(line1);
    painter->drawLine(line2);
}

void QReversi::draw_board_coordinate(QPainter* painter)
{
    {
        //横向
        QPoint p1;
        p1.setX(QReversi::koutlinealig + QReversi::kinerlinealig);
        p1.setY(QReversi::koutlinealig + QReversi::kscorealig);
        const int width = this->width() - 2 * (QReversi::koutlinealig + QReversi::kinerlinealig);
        const int rectheight = QReversi::kinerlinealig;
        const int rectwidth = width / Board::kNCols;
        QRect coodrect(p1.x(), p1.y(), rectwidth, rectheight);
        QString str;
        QFont font;
        font.setPixelSize(QReversi::kcoordinatefontpixelsize);
        painter->setFont(font);

        for(int i = 0; i != Board::kNCols; ++i)
        {
            str = QString("%1").arg(1 + i);
            //painter->drawRect(coodrect);
            painter->drawText(coodrect, Qt::AlignCenter, str);
            coodrect.moveTo(p1 += QPoint(rectwidth, 0));
        }
    }
    {
        //纵向
        QPoint p2;
        p2.setX(QReversi::koutlinealig);
        p2.setY(2 * QReversi::koutlinealig + QReversi::kinerlinealig);
        const int height = this->height() - QReversi::kscorealig - 2 * (QReversi::koutlinealig + QReversi::kinerlinealig);
        const int rectheight = height / Board::kNRows;
        const int rectwidth = QReversi::kinerlinealig;
        QRect coodrect(p2.x(), p2.y(), rectwidth, rectheight);
        QString str;
        QFont font;
        font.setPixelSize(QReversi::kcoordinatefontpixelsize);
        painter->setFont(font);

        for(int i = 0; i != Board::kNRows; ++i)
        {
            str = QString("%1").arg(char('A' + i));
            //painter->drawRect(coodrect);
            painter->drawText(coodrect, Qt::AlignCenter, str);
            coodrect.moveTo(p2 += QPoint(0, rectheight));
        }
    }
}

void QReversi::draw_score_and_winner(QPainter* painter)
{
    const QRect rect(QReversi::koutlinealig, 0, this->width(), QReversi::koutlinealig + QReversi::kscorealig);
    QFont font;
    font.setPixelSize(QReversi::kscorefontpixelsize);
    painter->setFont(font);
    QString scorestr = QString("Black score: %1, White score: %2.").arg(curboard.score(kBlack)).arg(curboard.score(kWhite));

    if (gameover)
    {
        //绘制胜利玩家
        if (winner != kEmpty)
        {
            scorestr.append(" Winner is ");
            QString str = winner == kBlack ? "Black" : "White";
            scorestr.append(str);
            scorestr.append(" Player!");
        }
    }
    else
    {
        //绘制当前着棋颜色
        if (this->thisturncolor == kBlack)
        { scorestr.append(" turn Color is Black."); }
        else if (this->thisturncolor == kWhite)
        { scorestr.append(" turn Color is White."); }
    }

    painter->drawText(rect, Qt::AlignVCenter, scorestr);
}


QPoint QReversi::trans_point(const QPoint& p) const
{
    //    QPoint t=p;
    //    t-=QPoint(kinerlinealig, kinerlinealig);
    //    t.setX(t.x() * (double)kinner_width / get_view_rect().width());
    //    t.setY(t.y() * (double)kinner_height / get_view_rect().height());
    //    return t;
    QPointF ff(p.x(), p.y());
    QPointF t = curtransform.map(ff);
    return QPoint(int(t.x()), int(t.y()));
}

QPoint QReversi::get_rect_center(int row, int col) const
{
    const int xsize = get_x_size();
    const int ysize = get_y_size();
    const int halfxsize = xsize / 2;
    const int halfysize = ysize / 2;
    return QPoint(col * xsize + halfxsize, row * ysize + halfysize);
}

void QReversi::get_row_col(const QPoint& p, int* row, int* col) const
{
    const int xsize = get_x_size();
    const int ysize = get_y_size();
    *col = p.x() / xsize;
    *row = p.y() / ysize;
}

void QReversi::setboard(const Board& board)
{
    this->curboard = board;
    update_board();
}

void QReversi::setgameover(Color color)
{
    this->gameover = true;
    this->winner = color;
}

void QReversi::resetgame()
{
    this->gameover = false;
    this->winner = kEmpty;
    this->thisturncolor = kEmpty;
    this->clickpos.rx() = -1;
    this->clickpos.ry() = -1;
    this->click_row = -1;
    this->click_col = -1;
}

void QReversi::setthisturncolor(Color color)
{
    this->thisturncolor = color;

    if (kWhite == color)
    { setCursor(cursor_white); }
    else
    { setCursor(cursor_black); }
}

void QReversi::update_board()
{
    update();
}

void QReversi::init_cursor()
{
    QPixmap bt1(":/icon/cursor_white.bmp");
    QCursor white(bt1);
    cursor_white = white;
    QPixmap bt2(":/icon/cursor_black.bmp");
    QCursor black(bt2);
    cursor_black = black;
}
