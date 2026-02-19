#pragma once

#include <qlist.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qfile.h>
#include "Procs.h"
#include "Settings.h"


class JsonDataManager {
public:

	// & => C#의 ref와 유사 ( 참조 )

	// 파일 저장 함수
	static bool saveFile(const QString& filePath, const QList<Procs>& dataList);

	// 파일 로드 함수
	static QList<Procs> loadFile(const QString& filePath);

	static void saveSettings(const QString& filePath, const Settings& settings);

	static Settings loadSettings(const QString& filePath);
};