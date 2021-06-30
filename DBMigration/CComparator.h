#pragma once
#include "CDBObject.h"
#include "CDBObjectStatusWrapper.h"
class CComparator
{
public:
	CDBObjectStatusWrapper Compare(	CDBObject const * aNewObject, 
									CDBObject const * aOldObject)
	{
		int Index = 0;
		CDBObjectStatusWrapper ret;

		if (aNewObject == nullptr)
			return CDBObjectStatusDeletedWrapper(aOldObject);
		if (aOldObject == nullptr)
			return CDBObjectStatusNewWrapper(aNewObject);
		

		if ((*aNewObject) == (*aOldObject))
			ret = CDBObjectStatusSameWrapper(aNewObject);
		else
			ret = CDBObjectStatusModifiedWrapper(aNewObject);
		while (auto Property = aNewObject->GetProperty(Index++))
		{
			ret.AddProperty(Compare (Property, aOldObject->FindProperty(Property)));
		}
		//тут еще надо убедиться что в старой версии объекта не было свойств, отсутствующих в новой
		return ret;
	}
};

