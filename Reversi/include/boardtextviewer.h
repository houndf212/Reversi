#ifndef BOARDTEXTVIEWER_H
#define BOARDTEXTVIEWER_H
#include <iostream>
#include "boardviewer.h"

using std::ostream;

class BoardTextViewer :
       public BoardViewer
{
public:
    BoardTextViewer(ostream &output): _output(output) {}
    virtual ~BoardTextViewer() {}
    virtual void draw(const Board &);
private:
    ostream &_output;
};

#endif //BOARDTEXTVIEWER_H
