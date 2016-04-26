#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addInstruction(const std::string& address, const std::string& instruction);
    void addMemoryWord(const std::string& address, const std::string& word);
    void addRegister(const std::string &name, const std::string &value);

    static void addWordToTable(QTableWidget* table, const std::string& key, const std::string& word);

private:
    Ui::MainWindow *ui;
    int highlightedInstructionRow;
    int highlightedMemoryRow;
    int highlightedRegisterRow;
    static const QColor defaultTableBackground;
    static const QColor activeTableBackground;

    void switchButtonStates(bool startState, bool stopState, bool advanceState, bool revertState);
    void clearHighlights();
    static void highlightTableRow(QTableWidget *table, int &previousRow, int row);

signals:
    void executionRequested();
    void stopRequested();
    void advanceRequested();
    void revertRequested();

public slots:
    void highlightInstructionRow(int row);
    void setMemory(int row, const std::string& newValue);
    void setRegister(int row, const std::string& newValue);
    void finishExecution();
    void setInstructionLabel(const std::string &name);
};

#endif // MAINWINDOW_H
