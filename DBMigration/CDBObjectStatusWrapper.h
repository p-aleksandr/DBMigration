#pragma once
#include "CDBObject.h"
#include "DBObjectStatus.h"
#include <vector>
class CDBObjectStatusWrapper
{
public:
	CDBObjectStatusWrapper() = default;

	CDBObjectStatusWrapper(	DBObjectStatus		aStatus,
							CDBObject const*	aObject)
		: mStatus(aStatus)
		, mObject(aObject)
	{
	};
	CDBObjectStatusWrapper &AddProperty(CDBObjectStatusWrapper const &aPropery)
	{
		Properties.push_back(aPropery);

		return *this;
	}
private:
		std::vector<CDBObjectStatusWrapper> Properties;
		DBObjectStatus		mStatus = DBObjectStatus::Undefined;
		CDBObject const*	mObject = nullptr;
	
};

class CDBObjectStatusNewWrapper : public CDBObjectStatusWrapper
{
public:
	CDBObjectStatusNewWrapper(CDBObject const* aObject)
		:CDBObjectStatusWrapper(DBObjectStatus::New,
			aObject)
	{
	};

};

class CDBObjectStatusDeletedWrapper : public CDBObjectStatusWrapper
{
public:
	CDBObjectStatusDeletedWrapper(CDBObject const* aObject)
		:CDBObjectStatusWrapper(DBObjectStatus::Deleted,
			aObject)
	{
	};
};


class CDBObjectStatusSameWrapper : public CDBObjectStatusWrapper
{
public:
	CDBObjectStatusSameWrapper(	CDBObject const* aObject)
		:CDBObjectStatusWrapper(DBObjectStatus::Same,
								aObject)
	{
	};
};


class CDBObjectStatusModifiedWrapper : public CDBObjectStatusWrapper
{
public:
	CDBObjectStatusModifiedWrapper(CDBObject const* aObject)
		:CDBObjectStatusWrapper(DBObjectStatus::Modified,
								aObject)
	{
	};
};
