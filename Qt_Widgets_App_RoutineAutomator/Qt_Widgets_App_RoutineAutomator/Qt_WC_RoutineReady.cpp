#include "Qt_WC_RoutineReady.h"

Qt_WC_RoutineReady::Qt_WC_RoutineReady(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 핵심 코드: 창의 테두리와 타이틀 바를 완전히 없애버립니다.
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	// 타이머 생성 및 연결 (1초 간격)
	countdownTimer = new QTimer(this);
	connect(countdownTimer, &QTimer::timeout, this, &Qt_WC_RoutineReady::updateCountdown);

	// 명시적 버튼 이벤트 연결 (버튼을 눌렀을 때 함수가 확실히 실행되도록 연결)
	connect(ui.pbtn_RoutineReadyY, &QPushButton::clicked, this, &Qt_WC_RoutineReady::on_pbtn_RoutineReadyYClicked);
	connect(ui.pbtn_RoutineReadyN, &QPushButton::clicked, this, &Qt_WC_RoutineReady::on_pbtn_RoutineReadyNClicked);

	// 초기 버튼 텍스트 설정 (헤더에서 10으로 설정된 remainingTime 적용)
	ui.pbtn_RoutineReadyY->setText(QString("예 ( %1 )").arg(remainingTime));

	// 타이머 시작 (1000ms = 1초)
	countdownTimer->start(1000);


}

Qt_WC_RoutineReady::~Qt_WC_RoutineReady() {

	// 창이 닫힐 때 타이머가 돌고 있다면 안전하게 정지
	if (countdownTimer->isActive()) {
		countdownTimer->stop();
	}
}

void Qt_WC_RoutineReady::updateCountdown() {
	remainingTime--;

	if (remainingTime <= 0) {
		countdownTimer->stop();
		on_pbtn_RoutineReadyYClicked();	// 0초가 되면 "예" 버튼 클릭 이벤트 호출
	}
	else {
		ui.pbtn_RoutineReadyY->setText(QString("예 ( %1 )").arg(remainingTime));
	}
}

void Qt_WC_RoutineReady::on_pbtn_RoutineReadyYClicked() {
	countdownTimer->stop();
	done(QDialog::Accepted);
}

void Qt_WC_RoutineReady::on_pbtn_RoutineReadyNClicked() {
	countdownTimer->stop();
	done(QDialog::Rejected);
}