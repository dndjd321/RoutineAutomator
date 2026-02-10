#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Widgets_App_RoutineAutomator.h"

class Qt_Widgets_App_RoutineAutomator : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Widgets_App_RoutineAutomator(QWidget *parent = nullptr);
    ~Qt_Widgets_App_RoutineAutomator();

private:
    Ui::Qt_Widgets_App_RoutineAutomatorClass ui;
};

