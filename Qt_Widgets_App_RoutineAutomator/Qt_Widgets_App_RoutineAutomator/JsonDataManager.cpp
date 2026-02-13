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

QList<Procs> loadFile(QString& filePath) {
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


	// 읽어온 데이터 반복문으로 하나의 proc씩 값 담기


	


	return qlist_proc;
}