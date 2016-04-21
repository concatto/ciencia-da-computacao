#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "processor.h"
#include "program.h"
#include "mainwindow.h"
#include <QObject>
#include <vector>

class Controller : public QObject
{
    Q_OBJECT

    MainWindow window;
    Processor processor;

    static std::vector<unsigned int> readMemoryFile(std::string path);

public:
    explicit Controller(QObject *parent = 0);

    void execute();

signals:

public slots:
};

#endif // CONTROLLER_H
