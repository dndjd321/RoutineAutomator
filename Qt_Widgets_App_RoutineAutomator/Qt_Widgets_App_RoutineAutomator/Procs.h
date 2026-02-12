#pragma once

#include <Qstring>

struct ProcInfo {
	QString name = "";	// 프로그램 명
	QString dir = "";	// 디렉토리 위치
	QString url = "";	// URL
};

struct Procs {
	int num = 0;				// 순서
	QString type = "";			// 타입 ( web / app )
	ProcInfo info = ProcInfo();	// 프로그램 정보
	int delay = 3;				// 프로그램 실행 지연시간 ( 딜레이 )
	bool dup = false;			// 중복 체크
};

