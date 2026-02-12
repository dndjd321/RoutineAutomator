#include "Qt_Widgets_App_RoutineAutomator.h"
#include "Procs.h"  // 프로세스 내용 정의 헤더 파일
#include "Qt_WC_AddProcDialog.h";
#include <QScreen>;
#include <QGuiApplication>


// 프로세스 내용 선언
Procs proc;


//// QTreeWidget Item 추가 후 가운데 정렬하는 함수 선언
//void SetTextAlignCenter(QTreeWidget* qtw);
//
//// QTreeWidget Item 추가 후 가운데 정렬하는 함수 정의
//void SetTextAlignCenter(QTreeWidget* qtw) {
//    //if (!item) { return; }   // item이 NULL 일 경우를 방지
//
//    QTreeWidgetItem* item = new QTreeWidgetItem(qtw);
//
//    for (int i = 0; i < qtw->columnCount(); i++) {
//        item->setTextAlignment(i, Qt::AlignCenter);
//    }
//}

Qt_Widgets_App_RoutineAutomator::Qt_Widgets_App_RoutineAutomator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    #pragma region 메인 창 크기 고정, 
    // 메인 창 크기 고정
    this->setFixedSize(700, 500);
    #pragma endregion

    #pragma region 메인 창 닫기, 최소화 활성화. 최대화는 비활성화
    // 메인 창 닫기, 최소화 버튼만 활성화. 최대화는 눌러도 화면이 커지지는 않음.
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    #pragma endregion

    #pragma region 메인 창 모니터 중앙으로 위치시키기
    // 메인 창 모니터 중앙으로 위치시키기
    // 모니터 화면 정보 가져오기
    QScreen* q_screen = QGuiApplication::primaryScreen();
    QRect q_rect = q_screen->geometry();
    // 화면 중심 좌표 구하기
    int rect_x = (q_rect.width() - this->width()) / 2;
    int rect_y = (q_rect.height() - this->height()) / 2;
    // 메인 창 위치 이동
    this->move(rect_x, rect_y);
    #pragma endregion

    #pragma region QTreeWidget Column Width Setting
    // QTreeWidget Column Width Setting
    ui.tw_procList->setColumnWidth(0, 75);
    ui.tw_procList->setColumnWidth(1, 75);
    ui.tw_procList->setColumnWidth(2, 370);
    ui.tw_procList->setColumnWidth(3, 75);
    #pragma endregion


    
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
    
    // Qt_WC_AddProcDialog 화면 띄우기를 위한 생성자 선언
    Qt_WC_AddProcDialog add_dialog(this);

    // 호출
    if (add_dialog.exec() == QDialog::Accepted) {
        // 임시 - 나중에 이 부분은 제거 예정
        proc.num = 1;
        proc.delay = 1;
        proc.dup = true;
        proc.type = "WEB";
        proc.info.name = "카톡";
        proc.info.dir = "내 PC";

        // 저장된 내용 들고오기
        Procs procdata = add_dialog.getProcsData();


        QTreeWidgetItem* tree_Item = new QTreeWidgetItem(ui.tw_procList);
        tree_Item->setData(0, Qt::DisplayRole, proc.num);
        tree_Item->setData(1, Qt::DisplayRole, proc.type);
        tree_Item->setData(2, Qt::DisplayRole, proc.info.name + " / " + proc.info.dir);
        tree_Item->setData(3, Qt::DisplayRole, proc.delay);
        tree_Item->setCheckState(4, proc.dup ? Qt::Checked : Qt::Unchecked);

        ui.tw_procList->addTopLevelItem(tree_Item);
    }

    //SetTextAlignCenter(ui.tw_procList);

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



