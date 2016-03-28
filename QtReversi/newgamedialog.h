#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include "ui_newgamedialog.h"

class NewGameDialog : public QDialog, public Ui::NewGameDialog
{
    Q_OBJECT
public:
    NewGameDialog(QWidget* parent = 0);
};

#endif // NEWGAMEDIALOG_H
