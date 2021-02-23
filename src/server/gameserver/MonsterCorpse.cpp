//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterCorpse.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MonsterCorpse.h"
#include "Monster.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
// 파라미터로 몬스터 객체를 받으면, 몬스터의 타입, 좌표, 방향을 저장한
// 후 몬스터의 인벤토리 안에 들어있던 아이템을 그래도 가지고 온다.
//////////////////////////////////////////////////////////////////////////////
MonsterCorpse::MonsterCorpse (Monster* pMonster)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);

	m_MonsterType = pMonster->getMonsterType();
	m_Name        = pMonster->getName();
	m_Dir         = pMonster->getDir();
	m_bhasHead    = true;

	m_bShrine     = false;

	setObjectID(pMonster->getObjectID());

	m_HostPartyID = 0;

	__END_CATCH
}

MonsterCorpse::MonsterCorpse (MonsterType_t MType, const string& name, Dir_t dir)
	throw (Error)
{
	__BEGIN_TRY

	m_MonsterType = MType;
	m_Name        = name;
	m_Dir         = dir;
	m_bhasHead    = true;

	m_bShrine     = false;

	m_HostPartyID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
MonsterCorpse::~MonsterCorpse()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// create
//////////////////////////////////////////////////////////////////////////////
void MonsterCorpse::create (const string & ownerID , Storage stroage , DWORD storageID , BYTE x , BYTE y, ItemID_t itemID)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destroy
//////////////////////////////////////////////////////////////////////////////
bool MonsterCorpse::destroy ()
	throw (Error)
{
	__BEGIN_TRY

	return true;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// save
//////////////////////////////////////////////////////////////////////////////
void MonsterCorpse::save (const string & ownerID , Storage stroage , DWORD storageID , BYTE x , BYTE y)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string MonsterCorpse::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterCorpse("
		<< "ObjectID:"     << (int)m_ObjectID
		<< ",MonsterName:" << m_Name
		<< ",MonsterType:" << (int)m_MonsterType 
		<< ",m_Dir:"       << Dir2String[m_Dir]
		<< ")";
	return msg.toString();

	__END_CATCH
}

