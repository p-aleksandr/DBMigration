#pragma once
#include "CDBObject.h"
class CTable: public CDBObject
{
public: 
	CTable(std::string_view	aName) :
		CDBObject(DBObjectType::Table,
			aName) 
	{
	};
};

class CField : public CDBObject
{
public:
	CField(std::string_view	aName) 
		:	CDBObject(	DBObjectType::Field,
						aName)
	{
	};
};

class CIndex : public CDBObject
{
public:
	CIndex(std::string_view	aName) 
		:	CDBObject(	DBObjectType::Index,
						aName)
	{
	};
};

class CProperty : public CDBObject
{
public:
	CProperty(	std::string_view	aName,
				std::string_view	aValue) 
		:	CDBObject(	DBObjectType::Property,
						aName,
						aValue)
	{
	};
};