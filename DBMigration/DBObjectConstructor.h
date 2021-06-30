#pragma once
#include <string_view>
#include "CDBObjectSuccessors.h"
class DBObjectConstructor
{
public:
	DBObjectConstructor(std::string_view aScript):
		mScript(aScript)
	{
	};
	virtual CDBObject* Construct() = 0;
private:
	std::string_view mScript;
};

class TableConstructor : public DBObjectConstructor
{
	public:
		TableConstructor(std::string_view aScript)
			: DBObjectConstructor(aScript)
		{
		};
		virtual CTable* Construct() 
		{
			//как-то парсим скрипт, скорее всего это еще одно семейство классов
			//один из наследников которых передается через консруктор
			return new CTable("");
		};
};

