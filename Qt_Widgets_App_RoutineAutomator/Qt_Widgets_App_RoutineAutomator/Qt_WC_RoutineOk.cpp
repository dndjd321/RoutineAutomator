#include "Qt_WC_RoutineOk.h"

Qt_WC_RoutineOk::Qt_WC_RoutineOk(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 핵심 코드: 창의 테두리와 타이틀 바를 완전히 없애버립니다.
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

Qt_WC_RoutineOk::~Qt_WC_RoutineOk()
{}

