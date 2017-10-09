#include "editorwindow.h"
#include "backusnaurparser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    EditorWindow w;
//    w.show();

    BackusNaurParser parser("<term> ::= <rec_expr> | expr");
    parser.dumpRules();

    return a.exec();
}
