#include "Qt_WC_AddProcDialog.h"
#include <qfiledevice.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <QScreen>;
#include <QGuiApplication>

Qt_WC_AddProcDialog::Qt_WC_AddProcDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


	// 연결 공식: connect(신호보낼객체, 신호종류, 받는객체, 실행할함수);
	// 예시 : connect(ui.pbtn_addProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onAddProcClicked);
	
	// 내 PC 에서 프로그램 찾기 및 선택 함수 선언
	connect(ui.pbtn_procSearch, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::SearchProcsFunc);

	// Type 선택 시 le_url Enabled true or false 처리 함수 선언
	//connect(ui.rb_chkApp, &QRadioButton::clicked, this, &Qt_WC_AddProcDialog::CheckChangeTypeFunc);
	//connect(ui.rb_chkWeb, &QRadioButton::clicked, this, &Qt_WC_AddProcDialog::CheckChangeTypeFunc);
	connect(ui.rb_chkApp, &QRadioButton::clicked, this, [=]() {
		CheckChangeTypeFunc(ui.rb_chkApp);
		});
	connect(ui.rb_chkWeb, &QRadioButton::clicked, this, [=]() {
		CheckChangeTypeFunc(ui.rb_chkWeb);
		});
	
	
	// Procs 값 저장하기 ( 이후 QMainWindow 에서 값 들고와서 QTreeWidget에 Item 등록 ) 
	connect(ui.pbtn_AddProcOk, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::AddProcOkFunc);

	// 프로그램 등록 X 
	connect(ui.pbtn_AddProcCancle, &QPushButton::clicked, this, &Qt_WC_AddProcDialog::AddProcCancleFunc);


}

Qt_WC_AddProcDialog::~Qt_WC_AddProcDialog()
{}



void Qt_WC_AddProcDialog::SearchProcsFunc() {
	/*QFileDialog qfd;

	qfd.open();

	qfd.close();*/

	QString filePath = QFileDialog::getOpenFileName(
		this,								// 부모 위젯
		"프로그램 선택",					// dialog 제목
		"C:\\",								// 시작 경로
		"실행파일(*.exe);;모든 파일(*.*)"	// 파일 필터(구분자는 ;;)
	);
	
	// filePath 값이 비어있지 않다면 조건부 실행
	if (!filePath.isEmpty()) {
		QFileInfo qf_info(filePath);
		QString fileName = qf_info.baseName();	// 프로그램 이름만 추출, 확장자 X
		ui.le_procName->setText(fileName);
		ui.le_procDir->setText(filePath);

		if (fileName.contains("chrome") || fileName.contains("firefox") || fileName.contains("opera") || fileName.contains("explorer")) {
			//ui.rb_chkWeb->QRadioButton::isChecked();
			CheckChangeTypeFunc(ui.rb_chkWeb);
		}
		else{
			//ui.rb_chkApp->QRadioButton::isChecked();
			CheckChangeTypeFunc(ui.rb_chkApp);
		}
	}

}

void Qt_WC_AddProcDialog::CheckChangeTypeFunc(QRadioButton* qrb) {
	qrb->setChecked(true);
}

void Qt_WC_AddProcDialog::AddProcOkFunc() {
	// Procs 데이터 저장
	Procs proc;

	proc.type = ui.rb_chkApp->QRadioButton::isChecked() == true ? "APP" : "WEB";	// 타입
	proc.delay = ui.sb_chkDelay->value();				// 딜레이
	proc.dup = ui.cb_chkDup->QCheckBox::isChecked();	// 중복
	proc.info.name = ui.le_procName->QLineEdit::text();	// 프로그램 명
	proc.info.dir = ui.le_procDir->QLineEdit::text();	// 프로그램 디렉토리
	proc.info.url = ui.le_url->QLineEdit::text();		// url 경로 ex ) https://www.naver.com/

	// .h 에 선언되어 있는 Procs에 값 저장
	setProc(proc);

	// ui 닫기
	this->accept();
}

void Qt_WC_AddProcDialog::AddProcCancleFunc() {
	// ui 닫기
	this->reject();
}




