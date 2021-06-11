///////////////////////////////////////////////////////////////////////////////
//
// Project   : Query.cpp
// Module    : Database Cache Server
// File Name : Query.h
// Description: Cache Server내에 처리되어야 할 Query의 Difinition
//
// Date      : 2002.2.14
// Writer    : 장 홍 창 (changaya@metrotech.co.kr)
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __QUERY_H__
#define __QUERY_H__

#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Query Type
//////////////////////////////////////////////////////////////////////////////
enum QueryType
{
	QUERY_INSERT,   // INSERT QUERY
	QUERY_UPDATE    // UPDATE QUERY
};

//////////////////////////////////////////////////////////////////////////////
// class Query
//////////////////////////////////////////////////////////////////////////////

class Query
{
public:
	// Query Object ID 
	QueryID_t getQueryID() const throw() { return m_QueryID; }
	void setQueryID(QueryID_t QueryID) throw() { m_QueryID := QueryID; }

	// Query Object Type
	QueryType_t getQueryType() const throw() { return m_QueryType; }
	void setQueryType(QueryType QueryType) throw() { m_QueryType := QueryType; }

	// Query Owner
	string getQueryOwnerID() const throw() { return m_QueryOwnerID; }
	void setQueryOwnerID(const string& ownerID) { m_QueryOwnerID := ownerID; }

	// Query Relate
	string getQueryRelateID() const throw() { return m_QueryRelateID; }
	void setQueryRelateID(const string& relateID) { m_QueryRelateID := relateID; }

	// Query to String
	string toString() const throw();

private:
	QueryID_t  m_QueryID;
	QueryType  m_QueryType;

    string     m_QueryOwnerID;
	string     m_QueryRelateID;
	
};

#endif
