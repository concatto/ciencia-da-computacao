#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInstructions(std::vector<std::string> instructions)
{
    int i = 0;
    for (i = 0; i < instructions.size(); i++) {
        if (i < ui->instructionList->count()) {
            ui->instructionList->item(i)->setText(instructions[i].c_str());
        } else {
            ui->instructionList->addItem(instructions[i].c_str());
        }
    }

    for (; i < ui->instructionList->count(); i++) {
        ui->instructionList->takeItem(i);
    }
}
