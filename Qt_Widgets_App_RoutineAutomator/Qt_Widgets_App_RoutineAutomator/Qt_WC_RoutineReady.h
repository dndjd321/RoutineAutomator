#pragma once

#include <QDialog>
#include <qtimer.h>
#include "ui_Qt_WC_RoutineReady.h"

class Qt_WC_RoutineReady : public QDialog
{
	Q_OBJECT

public:
	explicit Qt_WC_RoutineReady(QWidget *parent = nullptr);
	~Qt_WC_RoutineReady();

private:
	Ui::Qt_WC_RoutineReadyClass ui;
	QTimer* countdownTimer;
	int remainingTime = 10;

private slots:
	void on_pbtn_RoutineReadyYClicked();
	void on_pbtn_RoutineReadyNClicked();
	void updateCountdown();
};

