#ifndef BOARDVIEWER_H_INCLUDED
#define BOARDVIEWER_H_INCLUDED

class Board;
class BoardViewer
{
public:
    virtual void draw(const Board &) = 0;
    virtual ~BoardViewer() {}
protected:
    BoardViewer() {}
private:
    BoardViewer(const BoardViewer&);
    BoardViewer& operator=(const BoardViewer&);
};

#endif //BOARDVIEWER_H_INCLUDED
