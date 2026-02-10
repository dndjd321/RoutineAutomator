#include "Qt_Widgets_App_RoutineAutomator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Qt_Widgets_App_RoutineAutomator window;
    window.show();
    return app.exec();
}
