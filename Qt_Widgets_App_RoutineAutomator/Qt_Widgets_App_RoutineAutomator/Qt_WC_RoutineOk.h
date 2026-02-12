#pragma once

#include <QDialog>
#include "ui_Qt_WC_RoutineOk.h"

class Qt_WC_RoutineOk : public QDialog
{
	Q_OBJECT

public:
	Qt_WC_RoutineOk(QWidget *parent = nullptr);
	~Qt_WC_RoutineOk();

private:
	Ui::Qt_WC_RoutineOkClass ui;
};

