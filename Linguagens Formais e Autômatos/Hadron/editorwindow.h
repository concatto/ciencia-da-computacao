#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "ui_editorwindow.h"

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);

private:
    Ui::EditorWindow ui;
};

#endif // EDITORWINDOW_H
