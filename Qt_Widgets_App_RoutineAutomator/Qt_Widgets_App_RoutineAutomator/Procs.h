#pragma once

#include <Qstring>

struct ProcInfo {
	QString name = "";	// 명칭
	QString dir = "";	// 경로
	QString url = "";	// URL
};

struct Procs {
	int num = 0;				// 순서
	QString type = "";			// 타입 ( web / app )
	ProcInfo info = ProcInfo();	// 명칭 + 경로
	int delay = 3;				// 실행 지연 시간 ( 딜레이 )
	bool dup = false;			// 중복 체크 유무
};

