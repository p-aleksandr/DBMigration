#pragma once
#include <string_view>
#include "CDBObject.h"
class CDBObjectHistoryWrapper
{
public:
	CDBObjectHistoryWrapper(std::string_view	aTag,
							CDBObject	const& aObject)
		: mTag(aTag)
		, mObject(aObject)
	{
	};
private:
	std::string_view	mTag;
	CDBObject	const&	mObject;
};

