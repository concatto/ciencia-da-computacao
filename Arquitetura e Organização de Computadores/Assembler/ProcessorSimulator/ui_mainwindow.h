/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *advanceButton;
    QPushButton *revertButton;
    QSpacerItem *horizontalSpacer;
    QLabel *instructionLabel;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *instructionTableLabel;
    QTableWidget *instructionTable;
    QVBoxLayout *verticalLayout;
    QLabel *memoryTableLabel_2;
    QTableWidget *memoryTable;
    QVBoxLayout *verticalLayout_3;
    QLabel *registerTableLabel;
    QTableWidget *registerTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(618, 481);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(18);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        startButton->setMinimumSize(QSize(117, 0));
        startButton->setMaximumSize(QSize(16777213, 16777215));

        horizontalLayout_2->addWidget(startButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(stopButton);

        advanceButton = new QPushButton(centralWidget);
        advanceButton->setObjectName(QStringLiteral("advanceButton"));
        sizePolicy1.setHeightForWidth(advanceButton->sizePolicy().hasHeightForWidth());
        advanceButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(advanceButton);

        revertButton = new QPushButton(centralWidget);
        revertButton->setObjectName(QStringLiteral("revertButton"));

        horizontalLayout_2->addWidget(revertButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_2);

        instructionLabel = new QLabel(centralWidget);
        instructionLabel->setObjectName(QStringLiteral("instructionLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(14);
        instructionLabel->setFont(font);

        verticalLayout_4->addWidget(instructionLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        instructionTableLabel = new QLabel(centralWidget);
        instructionTableLabel->setObjectName(QStringLiteral("instructionTableLabel"));

        verticalLayout_2->addWidget(instructionTableLabel);

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
        memoryTableLabel_2 = new QLabel(centralWidget);
        memoryTableLabel_2->setObjectName(QStringLiteral("memoryTableLabel_2"));

        verticalLayout->addWidget(memoryTableLabel_2);

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
        registerTableLabel = new QLabel(centralWidget);
        registerTableLabel->setObjectName(QStringLiteral("registerTableLabel"));

        verticalLayout_3->addWidget(registerTableLabel);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simulador do Processador MIPS", 0));
        startButton->setText(QApplication::translate("MainWindow", "Iniciar execu\303\247\303\243o", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Parar", 0));
        advanceButton->setText(QApplication::translate("MainWindow", "Avan\303\247ar", 0));
        revertButton->setText(QApplication::translate("MainWindow", "Reverter", 0));
        instructionLabel->setText(QString());
        instructionTableLabel->setText(QApplication::translate("MainWindow", "Instru\303\247\303\265es", 0));
        QTableWidgetItem *___qtablewidgetitem = instructionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Endere\303\247o", 0));
        QTableWidgetItem *___qtablewidgetitem1 = instructionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Valor", 0));
        memoryTableLabel_2->setText(QApplication::translate("MainWindow", "Mem\303\263ria", 0));
        QTableWidgetItem *___qtablewidgetitem2 = memoryTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Endere\303\247o", 0));
        QTableWidgetItem *___qtablewidgetitem3 = memoryTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Valor", 0));
        registerTableLabel->setText(QApplication::translate("MainWindow", "Registradores", 0));
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
