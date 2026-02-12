#pragma once

#include <QDialog>
#include "ui_Qt_WC_AddProcDialog.h"
#include "Procs.h"

class Qt_WC_AddProcDialog : public QDialog
{
	Q_OBJECT

public:
	Qt_WC_AddProcDialog(QWidget *parent = nullptr);
	~Qt_WC_AddProcDialog();


	// QMainWindow인 RoutineAutomator 에서 값 가져올 때 함수 호출이 가능하도록 public에서 선언
	Procs getProc() { return _proc; }
	void setProc(Procs proc) { _proc = proc; }


private:
	Ui::Qt_WC_AddProcDialogClass ui;
	Procs _proc;

private slots:	// AddProcDialog.h 함수 선언
	void SearchProcsFunc();		// 내 PC 에서 프로그램 찾기 및 선택 함수 ( FileDialog 사용 예정 )
	void CheckChangeTypeFunc(QRadioButton* qrb);	// Type 변경 될 때 le_url Enabled true or false 설정 함수
	void AddProcOkFunc();		// 프로그램 추가 후 QDialog 닫기
	void AddProcCancleFunc();	// 프로그램 추가 없이 QDialog 닫기

};



