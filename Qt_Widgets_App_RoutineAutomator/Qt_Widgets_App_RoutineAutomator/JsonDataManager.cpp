#include "JsonDataManager.h"


bool JsonDataManager::saveFile(const QString& filePath, const QList<Procs>& dataList) {
	// json Array 형식 변수 선언
	QJsonArray qj_Array;

	// datalist에서 procs 형식에 데이터 값 한 묶음씩 계속 가져와서 qj_array에 추가
	for (const Procs& proc : dataList) {
		QJsonObject qj_obj;
		qj_obj["num"] = proc.num;
		qj_obj["type"] = proc.type;
		qj_obj["name"] = proc.info.name;
		qj_obj["dir"] = proc.info.dir;
		qj_obj["url"] = proc.info.url;
		qj_obj["delay"] = proc.delay;
		qj_obj["dup"] = proc.dup;

		qj_Array.append(qj_obj);
	}

	// 실제 json 파일형식으로 저장하기위한 객체 생성
	QJsonDocument qj_doc(qj_Array);
	QFile q_file(filePath);
	if (!q_file.open(QIODevice::WriteOnly)) return false;

	q_file.write(qj_doc.toJson(QJsonDocument::Indented));
	q_file.close();
	return true;
}

QList<Procs> JsonDataManager::loadFile(const QString& filePath) {
	QList<Procs> qlist_proc;
	QFile q_file(filePath);

	// 1. 파일이 있는지 체크
	if (!q_file.exists()) {	// 파일이 존재하지 않을 경우
		qDebug() << "파일이 존재하지 않습니다. :: " << filePath;
		return qlist_proc;	// 비어있는 QList 반환
	}

	if (!q_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "파일을 열거나 읽어오는데 실패하였습니다.";
		return qlist_proc;	// 비어있는 QList 반환
	}

	// json 파일 읽어오기
	QByteArray jsonData = q_file.readAll();
	// 읽은 후 파일 close
	q_file.close();

	// json 데이터 문서로 파싱하기
	QJsonDocument qj_doc = QJsonDocument::fromJson(jsonData);
	if (qj_doc.isNull() || !qj_doc.isArray()) {
		qDebug() << "Json 형식에 맞지 않습니다.";
		return qlist_proc;
	}

	// 읽어온 내용 QJsonArray에 담기
	QJsonArray j_array = qj_doc.array();

	// 읽어온 데이터 반복문으로 하나의 proc씩 값 담기
	// 4. JSON 배열을 QList<Procs>로 변환 (++i 국룰 사용!)
	for (int i = 0; i < j_array.size(); ++i) {
		QJsonObject obj = j_array[i].toObject();
		Procs p;

		// JSON 키값은 saveFile에서 썼던 명칭과 정확히 일치해야 합니다.
		p.num = obj["num"].toInt();
		p.type = obj["type"].toString();
		p.info.name = obj["name"].toString();
		p.info.dir = obj["dir"].toString();
		p.info.url = obj["url"].toString();
		p.delay = obj["delay"].toInt();
		p.dup = obj["dup"].toBool();

		qlist_proc.append(p);
	}

	return qlist_proc;
}

void JsonDataManager::saveSettings(const QString& filePath, const Settings& settings) {
	QJsonObject qj_obj;
	qj_obj["autoStart"] = settings.autoStart;
	qj_obj["uesTray"] = settings.useTray;

	QJsonDocument qj_doc(qj_obj);
	QFile q_file(filePath);

	if (q_file.open(QIODevice::WriteOnly)) {
		q_file.write(qj_doc.toJson());
		q_file.close();
	}
}

Settings JsonDataManager::loadSettings(const QString& filePath) {
	Settings settings;
	QFile q_file(filePath);

	// 파일이 없으면 기본 값 return
	if (!q_file.open(QIODevice::ReadOnly)) {
		return settings;
	}

	QByteArray q_array = q_file.readAll();
	QJsonDocument qj_doc = QJsonDocument::fromJson(q_array);
	QJsonObject qj_obj = qj_doc.object();

	settings.autoStart = qj_obj["autoStart"].toBool();
	settings.useTray = qj_obj["useTray"].toBool();

	return settings;
}