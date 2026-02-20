#include "Qt_WC_RoutineReady.h"

Qt_WC_RoutineReady::Qt_WC_RoutineReady(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 타이머 설정 (1초 간격)


	// 초기 버튼 텍스트 설정


	// 타이머 시작


}

Qt_WC_RoutineReady::~Qt_WC_RoutineReady()
{}

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