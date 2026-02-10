#pragma once


#include "ui_Qt_Widgets_App_RoutineAutomator.h"
#include <QtWidgets/QMainWindow>
#include <iostream>

class Qt_Widgets_App_RoutineAutomator : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Widgets_App_RoutineAutomator(QWidget *parent = nullptr);
    ~Qt_Widgets_App_RoutineAutomator();

private:
    Ui::Qt_Widgets_App_RoutineAutomatorClass ui;

private slots:  // 이벤트 발생 시 실행할 함수 선언 구역

    // 상단 프로세스 추가, 제거, 위 아래 순서 이동, 실행 함수
    void onAddProcClickFunc();
    void onRemoveProcClickFunc();
    void onMoveUpProcClickFunc();
    void onMoveDownProcClickFunc();
    void onRunProcClickFunc();

    // 하단 체크박스 구역 함수
    // 윈도우 시작 시 자동실행
    // 트레이 아이콘으로 실행 유지
    void onAutoStartCheckFunc();
    void onTrayIconCheckFunc();

    // 최하단 상태 체크 함수
    void onStatusChangeFunc();

};




