#pragma once
#include "DBObjectType.h"
//#include "CDBObjectStatusWrapper.h"

#include <string_view>
#include <vector>
#include <variant>
class CDBObject
{
public:
	CDBObject() = default;
	CDBObject(CDBObject const& aSource) = default;
	CDBObject(	DBObjectType		aType,
				std::string_view	aName,
				std::string_view	aValue="")	// тут надо подумать, возможно передавать std::variant или std::any если используется с++17
												// или юнион написать если более ранняя версия, а, возможно ,имеет смысл посмотреть в сторону 
												// шаблонов, но с ними будет проблема с добавлением свойств
		: mType(aType)
		, mName(aName)
		, mValue(aValue)
	{
	}

	template <typename T>
	CDBObject &AddProperty(T &&aObject)
	{
		Properties.push_back(aObject);

		return *this;
	}
	const CDBObject *FindProperty(CDBObject const *aTemplate) const
	{
		if (aTemplate == nullptr)
			return nullptr;

		for (size_t i=0; i< Properties.size(); i++)
			if (Properties[i].GetName() == aTemplate->GetName()&&
				Properties[i].GetType() == aTemplate->GetType())
				return &Properties[i];

		return nullptr;
	}

	const CDBObject* GetProperty(size_t aIndex) const
	{
		if (aIndex >= Properties.size())
			return nullptr;

		return &Properties[aIndex];
	}

	std::string_view GetName() const
	{
		return mName;
	}
	std::string_view GetValue() const
	{
		return mValue;
	}
	DBObjectType GetType() const
	{
		return mType;
	}
	
	bool operator == (CDBObject const& aOther) const
	{
		return (mType == aOther.GetType() &&
			mName == aOther.GetName() &&
			mValue == aOther.GetValue());

	}
		
private:
	std::vector<CDBObject>	Properties;
	DBObjectType			mType = DBObjectType::Undefined;
	std::string_view		mName = "";
	std::string_view		mValue = "";
};

