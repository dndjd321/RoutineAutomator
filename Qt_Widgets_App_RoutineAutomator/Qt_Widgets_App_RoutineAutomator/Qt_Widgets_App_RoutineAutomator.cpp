#include "Qt_Widgets_App_RoutineAutomator.h"
#include "Qt_WC_AddProcDialog.h"
#include "Qt_WC_RoutineOk.h"
#include "jsonDataManager.h"
#include <qscreen.h>
#include <qguiapplication.h>
#include <qmessagebox.h>
#include <qdesktopservices.h>
#include <qtimer.h>
#include <qprocess.h>
#include <qsettings.h>
#include <qdir.h>
#include <QCloseEvent>


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

    #pragma region 메인 창 크기 고정 
    // 메인 창 크기 고정
    this->setFixedSize(700, 470);
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
    ui.tw_procList->setColumnWidth(0, 60);
    ui.tw_procList->setColumnWidth(1, 60);
    ui.tw_procList->setColumnWidth(2, 205);
    ui.tw_procList->setColumnWidth(3, 205);
    ui.tw_procList->setColumnWidth(4, 60);
    #pragma endregion

    #pragma region ui와 함수 연결
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
    //connect(ui.cb_autoStart, &QCheckBox::checkStateChanged, this, &Qt_Widgets_App_RoutineAutomator::onStatusChangeFunc);
    connect(ui.cb_autoStart, &QCheckBox::checkStateChanged, this, [this](int state) {
        onStatusChangeFunc(state == Qt::Checked ? "자동 실행 활성화" : "자동 실행 비활성화");
        });

    // 트레이 아이콘으로 실행 유지 설정 함수 연결
    connect(ui.cb_trayIcon, &QCheckBox::checkStateChanged, this, &Qt_Widgets_App_RoutineAutomator::onTrayIconCheckFunc);
    
    #pragma endregion
    
    #pragma region Json 데이터 불러오기
    // json 파일 경로 저장
    j_FilePath = QCoreApplication::applicationDirPath() + "/routine_config.json";
    // 프로세스 정보 불러오기
    procs = JsonDataManager::loadFile(j_FilePath);

    // 프로세스 정보 추가
    for (auto& proc : procs) {
        addTreeItem(proc);
    }

    // json 파일 경로 저장
    s_FilePath = QCoreApplication::applicationDirPath() + "/settings.json";
    // 설정 정보 불러오기
    Settings currentSettings = JsonDataManager::loadSettings(s_FilePath);
    // 설정 정보 추가
    ui.cb_autoStart->setChecked(currentSettings.autoStart);
    ui.cb_trayIcon->setChecked(currentSettings.useTray);


    #pragma endregion

    #pragma region 프로그램 자동 실행 설정
    // 프로그램 시작 시 현재 레지스트리 상태를 읽어와서 체크박스에 반영
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    bool useTray = settings.value("UseTray", false).toBool();   // 기본값 false로 설정

    if (settings.contains("RoutineAutomator")) {
        ui.cb_autoStart->setChecked(true);
    }

    // useTray 값에 따라 CheckBox 상태 설정
    ui.cb_trayIcon->setChecked(useTray);
    
    

    // 프로그램 실행 시 들어온 인자 리스트 확인
    QStringList args = QCoreApplication::arguments();

    if (args.contains("-auto")) {
        onStatusChangeFunc("윈도우 자동 실행으로 시작됨. 루틴을 즉시 실행합니다.");
        if (ui.cb_trayIcon->isChecked()) {
            this->hide();
        }
        // UI가 완전히 뜨기 전일 수 있으므로 약간의 여유를 두고 시작하거나 즉시 호출
        QTimer::singleShot(1000, this, &Qt_Widgets_App_RoutineAutomator::startRoutine);
    }
    #pragma endregion




}

Qt_Widgets_App_RoutineAutomator::~Qt_Widgets_App_RoutineAutomator()
{}

// QTreeWidget Item 추가 함수 정의
void Qt_Widgets_App_RoutineAutomator::addTreeItem(Procs& p) {
    QTreeWidgetItem* tree_Item = new QTreeWidgetItem(ui.tw_procList);
    p.num = ui.tw_procList->topLevelItemCount();
    tree_Item->setData(0, Qt::DisplayRole, p.num);
    tree_Item->setData(1, Qt::DisplayRole, p.type);
    tree_Item->setData(2, Qt::DisplayRole, p.info.name + " / " + p.info.dir);
    tree_Item->setData(3, Qt::DisplayRole, p.info.url);
    tree_Item->setData(4, Qt::DisplayRole, p.delay);
    tree_Item->setCheckState(5, p.dup ? Qt::Checked : Qt::Unchecked);

    ui.tw_procList->addTopLevelItem(tree_Item);
}

// QTreeWidget Item 순서 재정렬 함수 정의
void Qt_Widgets_App_RoutineAutomator::reOrderTreeItems() {
    int count = ui.tw_procList->topLevelItemCount();

    // ++i 국룰을 사용하여 모든 아이템의 0번 컬럼(순번)을 갱신합니다.
    for (int i = 0; i < count; ++i) {
        QTreeWidgetItem* item = ui.tw_procList->topLevelItem(i);

        // UI상의 번호를 다시 세팅 (1번부터 시작할 경우 i + 1)
        item->setData(0, Qt::DisplayRole, i + 1);

        // 메모리 리스트의 num 값도 동기화하고 싶다면 여기서 수정합니다.
        if (i < procs.size()) {
            procs[i].num = i + 1;
        }
    }
}

// 프로세스 실행 함수 로직
void Qt_Widgets_App_RoutineAutomator::startRoutine() {
    if (procs.isEmpty()) {
        QMessageBox::information(this, "알림", "실행할 프로세스가 없습니다.");
        return;
    }

    // 루틴 시작 시 버튼들을 못 누르게 막음
    ui.pbtn_runProc->setEnabled(false);
    ui.pbtn_addProc->setEnabled(false);
    ui.pbtn_delProc->setEnabled(false);
    ui.pbtn_upProc->setEnabled(false);
    ui.pbtn_downProc->setEnabled(false);

    currentExecIdx = 0; // 0번(1번째)부터 시작

    ui.tw_procList->setCurrentItem(ui.tw_procList->topLevelItem(currentExecIdx));
    executeNextProcess();
}

// 다음 프로세스 실행 함수 로직
void Qt_Widgets_App_RoutineAutomator::executeNextProcess() {
    // 1. 모든 프로세스 실행 완료 체크
    if (currentExecIdx >= procs.size()) {
        // 마지막 프로세스까지 완료되면 완료창 띄우기 (Logic 3)
        Qt_WC_RoutineOk* okDialog = new Qt_WC_RoutineOk(this);
        okDialog->setAttribute(Qt::WA_DeleteOnClose); // 닫히면 메모리 해제
        okDialog->show();

        // 루틴 완료 후 버튼 활성화
        ui.pbtn_runProc->setEnabled(true);
        ui.pbtn_addProc->setEnabled(true);
        ui.pbtn_delProc->setEnabled(true);
        ui.pbtn_upProc->setEnabled(true);
        ui.pbtn_downProc->setEnabled(true);
        return;
    }

    onStatusChangeFunc((currentExecIdx + 1) + "번 프로세스 실행 중...");

    // 2. 현재 실행할 프로세스 정보 가져오기
    const Procs& proc = procs[currentExecIdx];

    // 3. 프로세스 실제 실행
    // 예: 외부 프로그램 실행(QProcess) 또는 웹 URL 열기 등
    if (proc.type == "WEB") {
        QDesktopServices::openUrl(QUrl(proc.info.url));
    }
    else {
        QString programPath = proc.info.dir; // 저장된 파일 경로

        if (!programPath.isEmpty()) {
            // 1. 실행할 파일이 실제로 존재하는지 체크
            if (QFile::exists(programPath)) {
                // 2. 프로그램 실행 (관리자 권한 계승)
                bool success = QProcess::startDetached(programPath, QStringList());

                if (!success) {
                    onStatusChangeFunc("프로그램 실행 실패:" + programPath);
                }
            }
            else {
                onStatusChangeFunc("파일을 찾을 수 없습니다:" + programPath);
            }
        }
    }

    // 4. 딜레이 대기 후 다음 프로세스 진행 (Logic 2)
    int delayMs = proc.delay * 1000; // 초 단위를 밀리초로 변환
    currentExecIdx++; // 다음 인덱스로 증가

    // 비동기 대기: UI가 멈추지 않으면서 지정된 시간 뒤에 다음 함수 호출
    QTimer::singleShot(delayMs, this, &Qt_Widgets_App_RoutineAutomator::executeNextProcess);
}

// 트레이 아이콘 생성 함수 로직
void Qt_Widgets_App_RoutineAutomator::createTrayIcon() {
    // 트레이 아이콘 객체 생성 이미 되어있는 상태이면 return;
    if (trayIcon != nullptr) return;

    // 트레이 아이콘 생성 및 기본 세팅
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("RoutineAutomator");

    // 트레이 아이콘 메뉴 세팅 ( 열기, 종료 )
    trayMenu = new QMenu(this);
    trayMenu->addAction("열기", this, &QWidget::showNormal);
    trayMenu->addAction("종료", this, &QCoreApplication::quit);

    // 트레이 아이콘에 메뉴 연결하기
    trayIcon->setContextMenu(trayMenu);

    // 트레이 아이콘 보이기
    trayIcon->show();
}

// 트레이 아이콘 제거 함수 로직
void Qt_Widgets_App_RoutineAutomator::removeTrayIcon() {
    // 트레이 아이콘이 이미 있을 경우 숨기고 제거하고 nullptr 초기화 진행
    if (trayIcon) {
        trayIcon->hide();
        delete trayIcon;
        trayIcon = nullptr;
    }
}

// 트레이 아이콘 체크 시 프로그램 실행 유지 설정 함수 로직
void Qt_Widgets_App_RoutineAutomator::closeEvent(QCloseEvent* event) {
    // 트레이 아이콘이 켜져 있고, 사용자가 트레이 기능을 쓰겠다고 한 경우
    if (trayIcon && trayIcon->isVisible() && ui.cb_trayIcon->isChecked()) {
        this->hide();      // 창만 숨김
        event->ignore();   // 종료 이벤트를 무시 (프로그램 유지)
    }
    else {
        // 트레이 아이콘을 안 쓰거나 체크 해제 상태라면 정상 종료
        event->accept();
    }
}

// 설정 정보 저장 함수 로직
void Qt_Widgets_App_RoutineAutomator::saveSetting() {
    Settings set;
    set.autoStart = ui.cb_autoStart->isChecked();
    set.useTray = ui.cb_trayIcon->isChecked();
    JsonDataManager::saveSettings(s_FilePath, set);
}


// 프로세스 추가 함수 로직
void Qt_Widgets_App_RoutineAutomator::onAddProcClickFunc() {
    
    // Qt_WC_AddProcDialog 화면 띄우기를 위한 생성자 선언
    Qt_WC_AddProcDialog add_dialog(this);

    // 호출
    if (add_dialog.exec() == QDialog::Accepted) {
        
        // 저장된 내용 들고오기
        Procs proc = add_dialog.getProc();

        // 1. procs 메모리에 proc 추가
        addTreeItem(proc);

        // 전체 데이터 포함된 QList<procs>에 방금 추가한 proc 내용 추가하기
        procs.append(proc);

        // 2. 파일에 전체 저장
        JsonDataManager::saveFile(j_FilePath, procs);

    }
}

// 프로세스 제거 함수 로직
void Qt_Widgets_App_RoutineAutomator::onRemoveProcClickFunc() {
    // 1. 현재 선택된 아이템 가져오기
    QTreeWidgetItem* currentItem = ui.tw_procList->currentItem();

    if (!currentItem) {
        QMessageBox::warning(this, "삭제 오류", "삭제할 항목을 먼저 선택해주세요.");
        return;
    }

    // 선택된 항목의 인덱스 확인 (0부터 시작)
    int index = ui.tw_procList->indexOfTopLevelItem(currentItem);

    // 2. 메모리 리스트(m_routineList)에서 제거
    if (index >= 0 && index < procs.size()) {
        procs.removeAt(index); // 특정 위치의 데이터 삭제
    }

    // 3. UI(QTreeWidget)에서 제거
    delete currentItem;

    // 4. 제거 후 순번 다시 정렬 (Logic 2)
    reOrderTreeItems();

    // 5. JSON 데이터 업데이트 (Logic 3)
    // 리스트 전체를 다시 저장하여 파일 내용을 최신화합니다.
    if (JsonDataManager::saveFile(j_FilePath, procs)) {
        qDebug() << "삭제 후 JSON 업데이트 완료";
    }
}

// 프로세스 순서 위로 이동하는 함수 로직
void Qt_Widgets_App_RoutineAutomator::onMoveUpProcClickFunc() {
    QTreeWidgetItem* currentItem = ui.tw_procList->currentItem();
    if (!currentItem) return;

    int index = ui.tw_procList->indexOfTopLevelItem(currentItem);

    // 가장 위(0번)가 아니어야 위로 올릴 수 있음
    if (index > 0) {
        // 1. 메모리 리스트 순서 교체 (index-1 과 index 교체)
        procs.swapItemsAt(index, index - 1);

        // 2. UI 순서 교체
        // 현재 아이템을 잠시 떼어냈다가 위 칸에 다시 끼워 넣음
        ui.tw_procList->takeTopLevelItem(index);
        ui.tw_procList->insertTopLevelItem(index - 1, currentItem);

        // 3. 포커스 유지
        ui.tw_procList->setCurrentItem(currentItem);

        // 4. 번호 재정렬 및 JSON 저장
        reOrderTreeItems();
        JsonDataManager::saveFile(j_FilePath, procs);
    }
}

// 프로세스 순서 아래로 이동하는 함수 로직
void Qt_Widgets_App_RoutineAutomator::onMoveDownProcClickFunc() {
    QTreeWidgetItem* currentItem = ui.tw_procList->currentItem();
    if (!currentItem) return;

    int index = ui.tw_procList->indexOfTopLevelItem(currentItem);
    int lastIndex = ui.tw_procList->topLevelItemCount() - 1;

    // 가장 아래가 아니어야 아래로 내릴 수 있음
    if (index < lastIndex) {
        // 1. 메모리 리스트 순서 교체 (index 와 index+1 교체)
        procs.swapItemsAt(index, index + 1);

        // 2. UI 순서 교체
        ui.tw_procList->takeTopLevelItem(index);
        ui.tw_procList->insertTopLevelItem(index + 1, currentItem);

        // 3. 포커스 유지
        ui.tw_procList->setCurrentItem(currentItem);

        // 4. 번호 재정렬 및 JSON 저장
        reOrderTreeItems();
        JsonDataManager::saveFile(j_FilePath , procs);
    }
}

// 프로세스 실행 함수 로직
void Qt_Widgets_App_RoutineAutomator::onRunProcClickFunc() {
    startRoutine();
}

// 윈도우 시작 시 자동 실행 설정 함수 로직
void Qt_Widgets_App_RoutineAutomator::onAutoStartCheckFunc(int state) {
    // 윈도우 레지스트리 시작 프로그램 경로
    QString regPath = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    QSettings settings(regPath, QSettings::NativeFormat);

    // 프로그램 이름 (레지스트리에 표시될 키 이름)
    QString appName = "RoutineAutomator";
    // 현재 실행 파일의 전체 경로
    QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    QString autoRunPath = QString("\"%1\" -auto").arg(appPath);

    if (state == Qt::Checked) {
        // 1. 체크됨 -> 레지스트리에 등록
        settings.setValue(appName, autoRunPath);
        //qDebug() << "자동 실행 등록 완료:" << appPath;
    }
    else {
        // 2. 체크 해제됨 -> 레지스트리에서 삭제
        settings.remove(appName);
        //qDebug() << "자동 실행 해제 완료";
    }

    saveSetting();
}

// 트레리 아이콘 설정 함수 로직
void Qt_Widgets_App_RoutineAutomator::onTrayIconCheckFunc(int state) {
    if (state == Qt::Checked) {
        createTrayIcon();
    }
    else {
        removeTrayIcon();
    }

    saveSetting();
}

// 상태 Label Text 변경 함수 로직
void Qt_Widgets_App_RoutineAutomator::onStatusChangeFunc(const QString& status) {
    ui.lb_status->setText(status);
	qDebug() << status;
}



