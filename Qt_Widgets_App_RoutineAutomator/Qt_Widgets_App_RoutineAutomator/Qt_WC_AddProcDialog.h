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


	// Procs에 대한 데이터를 저장할 Procs 값 반환하는 함수 생성하기
	// QMainWindow인 RoutineAutomator 에서 사용 가능하도록 public에서 선언
	Procs getProc() { return _proc; }
	void setProc(Procs proc) { _proc = proc; }


private:
	Ui::Qt_WC_AddProcDialogClass ui;
	Procs _proc;

private slots:	// AddProcDialog.h 에서 사용할 이벤트 함수들 선언
	void SearchProcsFunc();		// 내 PC 에 있는 프로그램 찾아서 선택하는 함수
	void CheckChangeTypeFunc();	// Type 변경에 따라 le_url Enabled true or false 처리 시키는 함수
	void AddProcOkFunc();		// 기입한 내용을 토대로 루틴 추가하는 함수 
	void AddProcCancleFunc();	// 루틴 추가 거부 함수 

};



