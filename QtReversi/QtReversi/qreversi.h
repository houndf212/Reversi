#ifndef QREVERSI_H
#define QREVERSI_H

#include <QWidget>
#include <QRect>
#include <QLine>
#include <QPoint>
#include <QTransform>
#include <QCursor>

#include "board.h"
#include "threadgame.h"
#include "guiplayer.h"
#include "boardguiviewer.h"



class QReversi : public QWidget
{
    Q_OBJECT
public:
    enum GameType { PVP, PVC, CVC };
public:
    QReversi(QWidget* parent = 0);
    ~QReversi();
    void CreateNewGame(QReversi::GameType type, int pclevel);

signals:
    void sendmovepos(const MovePos& p);
public slots:
    void setboard(const Board&);
    void setgameover(Color color);
    void setthisturncolor(Color color);
protected:
    void paintEvent(QPaintEvent*);
    //void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent* e);
private:
    //杀死线程
    void killandwaitgamethread();
    //获得外边框
    QRect get_out_rect() const;
    //获得视口矩阵
    QRect get_view_rect() const;
    //获得棋盘布线
    void get_board_matrix_lines();
    //绘制棋盘格子
    void draw_board_matrix(QPainter*);
    //绘制坐标
    void draw_board_coordinate(QPainter*);
    //绘制一个棋子
    void draw_circle(QPainter* painter, int row, int col, Color color);
    //绘制所有棋子
    void draw_chesses(QPainter*);
    //绘制最后一步
    void draw_lastmove(QPainter*);
    //绘制得分
    void draw_score_and_winner(QPainter*);

    //从坐标获得所在行列
    void get_row_col(const QPoint& p, int* row, int* col) const;
    //从行列获得格子中心点
    QPoint get_rect_center(int row, int col) const;
    //把鼠标点击点转化为“视窗”坐标
    QPoint trans_point(const QPoint&) const;

    //保存鼠标点击的点
    QPoint clickpos;
    int click_row;
    int click_col;
    //保存棋盘（所有棋子信息）
    Board curboard;
    Color thisturncolor;
    Color winner;
    bool gameover;
    void resetgame();

    QTransform curtransform;
public:
    static const int kscorealig = 20;
    static const int koutlinealig = 20;
    static const int kinerlinealig = 25;
    static const int kinner_width = 80 * 8;
    static const int kinner_height = 80 * 8;
    static const int kradius =int( kinner_width / (Board::kNCols * 2) * 4.0 / 5 );

    static const int kscorefontpixelsize = 20;
    static const int kcoordinatefontpixelsize = 18;
    int get_x_size() const;
    int get_y_size() const;

    //保存棋盘布线
    QLine board_row_lines[Board::kNRows + 1];
    QLine board_col_lines[Board::kNCols + 1];

private:

    GUIPlayer* player_white;
    GUIPlayer* player_black;
    BoardGUIViewer* viewer;
    ThreadGame* game;
    void update_board();
    void init_cursor();
    QCursor cursor_white;
    QCursor cursor_black;

};

inline int QReversi::get_x_size() const
{
    return kinner_width / Board::kNRows;
}

inline int QReversi::get_y_size() const
{
    return kinner_height / Board::kNCols;
}

#endif // QREVERSI_H
