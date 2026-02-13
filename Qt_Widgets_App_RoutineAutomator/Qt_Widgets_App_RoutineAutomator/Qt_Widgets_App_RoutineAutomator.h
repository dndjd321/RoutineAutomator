#pragma once


#include "ui_Qt_Widgets_App_RoutineAutomator.h"
#include "Procs.h"
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

    //QList<Procs> procs = QList<Procs>(); //  C# 방식 
    QList<Procs> procs; // C++ 에서 일반적으로 선언하는 방식
    QString j_FilePath;  // json 파일 저장 경로
    

private slots:  // UI 이벤트 처리 함수

    // 버튼 클릭 제어 함수
    void onAddProcClickFunc();
    void onRemoveProcClickFunc();
    void onMoveUpProcClickFunc();
    void onMoveDownProcClickFunc();
    void onRunProcClickFunc();

    // 체크박스 제어 함수
    void onAutoStartCheckFunc();
    void onTrayIconCheckFunc();

    // 현재 진행 상황 제어 함수
    void onStatusChangeFunc();

};




