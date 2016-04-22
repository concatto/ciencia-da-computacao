/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *startButton;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *instructionLabel;
    QTableWidget *instructionTable;
    QVBoxLayout *verticalLayout;
    QLabel *memoryLabel;
    QTableWidget *memoryTable;
    QVBoxLayout *verticalLayout_3;
    QLabel *registerLabel;
    QTableWidget *registerTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(618, 481);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        verticalLayout_4->addWidget(startButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        instructionLabel = new QLabel(centralWidget);
        instructionLabel->setObjectName(QStringLiteral("instructionLabel"));

        verticalLayout_2->addWidget(instructionLabel);

        instructionTable = new QTableWidget(centralWidget);
        if (instructionTable->columnCount() < 2)
            instructionTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        instructionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        instructionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        instructionTable->setObjectName(QStringLiteral("instructionTable"));
        instructionTable->setColumnCount(2);
        instructionTable->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(instructionTable);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        memoryLabel = new QLabel(centralWidget);
        memoryLabel->setObjectName(QStringLiteral("memoryLabel"));

        verticalLayout->addWidget(memoryLabel);

        memoryTable = new QTableWidget(centralWidget);
        if (memoryTable->columnCount() < 2)
            memoryTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        memoryTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        memoryTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        memoryTable->setObjectName(QStringLiteral("memoryTable"));
        memoryTable->setColumnCount(2);
        memoryTable->horizontalHeader()->setCascadingSectionResizes(false);
        memoryTable->horizontalHeader()->setDefaultSectionSize(100);
        memoryTable->horizontalHeader()->setStretchLastSection(false);
        memoryTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(memoryTable);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        registerLabel = new QLabel(centralWidget);
        registerLabel->setObjectName(QStringLiteral("registerLabel"));

        verticalLayout_3->addWidget(registerLabel);

        registerTable = new QTableWidget(centralWidget);
        if (registerTable->columnCount() < 2)
            registerTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        registerTable->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        registerTable->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        registerTable->setObjectName(QStringLiteral("registerTable"));
        registerTable->setColumnCount(2);
        registerTable->horizontalHeader()->setCascadingSectionResizes(false);
        registerTable->horizontalHeader()->setDefaultSectionSize(100);
        registerTable->horizontalHeader()->setStretchLastSection(false);
        registerTable->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(registerTable);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        startButton->setText(QApplication::translate("MainWindow", "Iniciar execu\303\247\303\243o", 0));
        instructionLabel->setText(QApplication::translate("MainWindow", "Instru\303\247\303\265es", 0));
        QTableWidgetItem *___qtablewidgetitem = instructionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Endere\303\247o", 0));
        QTableWidgetItem *___qtablewidgetitem1 = instructionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Valor", 0));
        memoryLabel->setText(QApplication::translate("MainWindow", "Mem\303\263ria", 0));
        QTableWidgetItem *___qtablewidgetitem2 = memoryTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Endere\303\247o", 0));
        QTableWidgetItem *___qtablewidgetitem3 = memoryTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Valor", 0));
        registerLabel->setText(QApplication::translate("MainWindow", "Registradores", 0));
        QTableWidgetItem *___qtablewidgetitem4 = registerTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Nome", 0));
        QTableWidgetItem *___qtablewidgetitem5 = registerTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Valor", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
