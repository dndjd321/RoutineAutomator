#include "Qt_Widgets_App_RoutineAutomator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // 마지막 창이 닫혀도 애플리케이션을 종료하지 않음
    QApplication::setQuitOnLastWindowClosed(false);

    Qt_Widgets_App_RoutineAutomator window;
    window.show();
    return app.exec();
}
