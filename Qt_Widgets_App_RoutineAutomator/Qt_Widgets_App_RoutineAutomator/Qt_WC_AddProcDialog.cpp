#include "Qt_WC_AddProcDialog.h"
#include <qfiledevice.h>
#include <qfileinfo.h>
#include <QScreen>;
#include <QGuiApplication>

Qt_WC_AddProcDialog::Qt_WC_AddProcDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


	// 연결 공식: connect(신호보낼객체, 신호종류, 받는객체, 실행할함수);
	// 예시 : connect(ui.pbtn_addProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onAddProcClicked);
	
	// 내PC 에서 프로그램 찾고 선택하는 함수
	connect(ui.pbtn_procSearch, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::SearchProcsFunc);

	// Type 변경 되었을 때 le_url Enabled true or false 설정하는 함수
	connect(ui.rb_chkApp, &QPushButton::isChecked, this, &Qt_WC_AddProcDialog::CheckChangeTypeFunc);
	connect(ui.rb_chkWeb, &QPushButton::isChecked, this, &Qt_WC_AddProcDialog::CheckChangeTypeFunc);
	
	// Procs 에 데이터 추가 후 화면 종료 ( QMainWindow 에서 데이터 가져갈 거임) 
	connect(ui.pbtn_AddProcOk, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::AddProcOkFunc);

	// 데이터 추가 없이 화면 종료
	connect(ui.pbtn_AddProcCancle, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::AddProcCancleFunc);


}

Qt_WC_AddProcDialog::~Qt_WC_AddProcDialog()
{}



void Qt_WC_AddProcDialog::SearchProcsFunc() {

}

void Qt_WC_AddProcDialog::CheckChangeTypeFunc() {

}

void Qt_WC_AddProcDialog::AddProcOkFunc() {
	// Procs에 데이터 담기


	// ui 닫기
	this->reject();
}

void Qt_WC_AddProcDialog::AddProcCancleFunc() {
	// ui 닫기
	this->reject();
}




