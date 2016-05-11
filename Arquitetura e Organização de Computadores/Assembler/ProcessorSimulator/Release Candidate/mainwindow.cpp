#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QMessageBox>

const QColor MainWindow::defaultTableBackground = QColor(255, 255, 255);
const QColor MainWindow::activeTableBackground = QColor(127, 200, 127);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), highlightedInstructionRow(0), highlightedMemoryRow(0), highlightedRegisterRow(0)
{
    ui->setupUi(this);
    QTableWidget* tables[] = {ui->instructionTable, ui->memoryTable, ui->registerTable};
    for (QTableWidget* table : tables) {
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        table->verticalHeader()->setDefaultSectionSize(22);
    }

    QObject::connect(ui->startButton, &QPushButton::clicked, [&]() {
        switchButtonStates(false, true, false, false);
        emit executionRequested();
    });
    QObject::connect(ui->stopButton, &QPushButton::clicked, [&]() { emit stopRequested(); });
    QObject::connect(ui->advanceButton, &QPushButton::clicked, [&]() { emit advanceRequested(); });
    QObject::connect(ui->revertButton, &QPushButton::clicked, [&]() {
        emit revertRequested();
        clearHighlights();
        setInstructionLabel("");
    });

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));
    finishExecution(); //Initialize button states
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

void MainWindow::switchButtonStates(bool startState, bool stopState, bool advanceState, bool revertState)
{
    ui->startButton->setEnabled(startState);
    ui->stopButton->setEnabled(stopState);
    ui->advanceButton->setEnabled(advanceState);
    ui->revertButton->setEnabled(revertState);

    qApp->processEvents();
}

void MainWindow::clearHighlights()
{
    if (highlightedInstructionRow < ui->instructionTable->rowCount()) {
        ui->instructionTable->item(highlightedInstructionRow, 0)->setBackgroundColor(defaultTableBackground);
        ui->instructionTable->item(highlightedInstructionRow, 1)->setBackgroundColor(defaultTableBackground);
    }

    if (highlightedMemoryRow < ui->memoryTable->rowCount()) {
        ui->memoryTable->item(highlightedMemoryRow, 0)->setBackgroundColor(defaultTableBackground);
        ui->memoryTable->item(highlightedMemoryRow, 1)->setBackgroundColor(defaultTableBackground);
    }

    if (highlightedRegisterRow < ui->registerTable->rowCount()) {
        ui->registerTable->item(highlightedRegisterRow, 0)->setBackgroundColor(defaultTableBackground);
        ui->registerTable->item(highlightedRegisterRow, 1)->setBackgroundColor(defaultTableBackground);
    }
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

void MainWindow::finishExecution()
{
    clearHighlights();
    switchButtonStates(true, false, true, true);
}

void MainWindow::highlightInstructionRow(int row)
{
    highlightTableRow(ui->instructionTable, highlightedInstructionRow, row);
}

void MainWindow::setInstructionLabel(const std::string& name)
{
    ui->instructionLabel->setText(name.c_str());
}

void MainWindow::showError(const std::string& message)
{
    QMessageBox::critical(this, "Erro", message.c_str());
}
