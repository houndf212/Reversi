#ifndef BOARDGUIVIEWER_H
#define BOARDGUIVIEWER_H

#include <QObject>
#include "boardviewer.h"
#include "board.h"

class BoardGUIViewer : public QObject, public BoardViewer
{
    Q_OBJECT
public:
    explicit BoardGUIViewer(QObject* parent = 0);
    virtual void draw(const Board&);
signals:
    void sendboard(const Board&);
public slots:

};

#endif // BOARDGUIVIEWER_H
