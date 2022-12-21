/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
