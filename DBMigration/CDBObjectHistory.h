#pragma once
#include "CDBObject.h"
#include <map>
#include <string_view>
class CDBObjectHistory
{
public:
	void Store(std::string_view aTag, CDBObject const &aObject)
	{
		// надо бы добавить проверку того, что добавляем все время один и тот же объект
		// для этого при первой вставке надо сохранить шаблон вставляемого объекта и каждый 
		// раз при последующих вставках сравнивать
		mHistory.insert({ aTag, aObject });
	}
	CDBObject Get(std::string_view aTag)
	{
		return mHistory[aTag];
	}
private:
	std::map<std::string_view, CDBObject> mHistory;
};

