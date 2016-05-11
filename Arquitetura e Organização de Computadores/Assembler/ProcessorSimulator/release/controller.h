#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "processor.h"
#include "mainwindow.h"
#include <QObject>
#include <vector>
#include <functional>
#include <string>

class Controller : public QObject
{
    Q_OBJECT

    MainWindow window;
    Processor processor;

    static void readHexadecimalFile(std::string path, std::function<void (unsigned int)> callback);

public:
    explicit Controller(QObject *parent = 0);

    void execute();
signals:

public slots:
};

#endif // CONTROLLER_H
