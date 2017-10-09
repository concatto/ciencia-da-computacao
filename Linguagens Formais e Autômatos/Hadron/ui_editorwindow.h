/********************************************************************************
** Form generated from reading UI file 'editorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORWINDOW_H
#define UI_EDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditorWindow)
    {
        if (EditorWindow->objectName().isEmpty())
            EditorWindow->setObjectName(QStringLiteral("EditorWindow"));
        EditorWindow->resize(800, 600);
        menubar = new QMenuBar(EditorWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        EditorWindow->setMenuBar(menubar);
        centralwidget = new QWidget(EditorWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        EditorWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(EditorWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EditorWindow->setStatusBar(statusbar);

        retranslateUi(EditorWindow);

        QMetaObject::connectSlotsByName(EditorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EditorWindow)
    {
        EditorWindow->setWindowTitle(QApplication::translate("EditorWindow", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditorWindow: public Ui_EditorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORWINDOW_H
