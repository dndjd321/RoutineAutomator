#include "Qt_Widgets_App_RoutineAutomator.h"

Qt_Widgets_App_RoutineAutomator::Qt_Widgets_App_RoutineAutomator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    
    // 연결 공식: connect(신호보낼객체, 신호종류, 받는객체, 실행할함수);
    // 예시 : connect(ui.pbtn_addProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onAddProcClicked);

    // 프로세스 추가 함수 연결
    connect(ui.pbtn_addProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onAddProcClickFunc);
    
    // 프로세스 제거 함수 연결
    connect(ui.pbtn_delProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onRemoveProcClickFunc);

    // 프로세스 순서 위로 이동 함수 연결
    connect(ui.pbtn_upProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onMoveUpProcClickFunc);

    // 프로세스 순서 아래로 이동 함수 연결
    connect(ui.pbtn_downProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onMoveDownProcClickFunc);

    // 프로세스 실행 함수 연결
    connect(ui.pbtn_runProc, &QPushButton::clicked, this, &Qt_Widgets_App_RoutineAutomator::onRunProcClickFunc);

    // 윈도우 시작 시 프로그램 자동 실행 체크박스 설정 함수 연결
    connect(ui.cb_autoStart, &QCheckBox::checkStateChanged, this, &Qt_Widgets_App_RoutineAutomator::onStatusChangeFunc );

    // 트레이 아이콘으로 실행 유지 설정 함수 연결
    connect(ui.cb_trayIcon, &QCheckBox::checkStateChanged, this, &Qt_Widgets_App_RoutineAutomator::onTrayIconCheckFunc);

    // 현재 진행 상황 label 설정 함수 연결
    connect(ui.lb_status, &QLabel::setText, this, &Qt_Widgets_App_RoutineAutomator::onStatusChangeFunc);


}

Qt_Widgets_App_RoutineAutomator::~Qt_Widgets_App_RoutineAutomator()
{}


// 프로세스 추가 함수 로직
void Qt_Widgets_App_RoutineAutomator::onAddProcClickFunc() {
    
}

// 프로세스 제거 함수 로직
void Qt_Widgets_App_RoutineAutomator::onRemoveProcClickFunc() {

}

// 프로세스 순서 위로 이동하는 함수 로직
void Qt_Widgets_App_RoutineAutomator::onMoveUpProcClickFunc() {

}

// 프로세스 순서 아래로 이동하는 함수 로직
void Qt_Widgets_App_RoutineAutomator::onMoveDownProcClickFunc() {

}

// 프로세스 실행 함수 로직
void Qt_Widgets_App_RoutineAutomator::onRunProcClickFunc() {

}

// 윈도우 시작 시 자동 실행 설정 함수 로직
void Qt_Widgets_App_RoutineAutomator::onAutoStartCheckFunc() {

}

// 트레리 아이콘 설정 함수 로직
void Qt_Widgets_App_RoutineAutomator::onTrayIconCheckFunc() {

}

// 상태 Label Text 변경 함수 로직
void Qt_Widgets_App_RoutineAutomator::onStatusChangeFunc() {

}



