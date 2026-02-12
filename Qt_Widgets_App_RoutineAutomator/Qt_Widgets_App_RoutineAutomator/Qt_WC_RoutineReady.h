#pragma once

#include <QDialog>
#include "ui_Qt_WC_RoutineReady.h"

class Qt_WC_RoutineReady : public QDialog
{
	Q_OBJECT

public:
	Qt_WC_RoutineReady(QWidget *parent = nullptr);
	~Qt_WC_RoutineReady();

private:
	Ui::Qt_WC_RoutineReadyClass ui;
};

