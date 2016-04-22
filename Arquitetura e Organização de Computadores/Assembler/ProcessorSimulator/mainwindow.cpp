#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

const QColor MainWindow::defaultTableBackground = QColor(255, 255, 255);
const QColor MainWindow::activeTableBackground = QColor(127, 200, 127);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), highlightedInstructionRow(0), highlightedMemoryRow(0), highlightedRegisterRow(0)
{
    ui->setupUi(this);
    ui->instructionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->registerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(ui->startButton, &QPushButton::clicked, [&]() { emit executionRequested(); });
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,size(), qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addInstruction(const std::string& address, const std::string& instruction)
{
    addWordToTable(ui->instructionTable, address, instruction);
}

void MainWindow::addMemoryWord(const std::string& address, const std::string &word)
{
    addWordToTable(ui->memoryTable, address, word);
}

void MainWindow::addRegister(const std::string& name, const std::string& value)
{
    addWordToTable(ui->registerTable, name, value);
}

void MainWindow::addWordToTable(QTableWidget* table, const std::string& key, const std::string &word)
{
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(key.c_str()));
    table->setItem(row, 1, new QTableWidgetItem(word.c_str()));
}

void MainWindow::highlightTableRow(QTableWidget* table, int& previousRow, int row) {
    table->item(previousRow, 0)->setBackgroundColor(defaultTableBackground);
    table->item(previousRow, 1)->setBackgroundColor(defaultTableBackground);

    table->item(row, 0)->setBackgroundColor(activeTableBackground);
    table->item(row, 1)->setBackgroundColor(activeTableBackground);

    previousRow = row;
}

void MainWindow::setMemory(int row, const std::string &newValue)
{
    ui->memoryTable->setItem(row, 1, new QTableWidgetItem(newValue.c_str()));
    highlightTableRow(ui->memoryTable, highlightedMemoryRow, row);
}

void MainWindow::setRegister(int row, const std::string &newValue)
{
    ui->registerTable->setItem(row, 1, new QTableWidgetItem(newValue.c_str()));
    highlightTableRow(ui->registerTable, highlightedRegisterRow, row);
}

void MainWindow::highlightInstructionRow(int row)
{
    highlightTableRow(ui->instructionTable, highlightedInstructionRow, row);
}
