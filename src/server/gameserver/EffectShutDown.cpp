//----------------------------------------------------------------------
//
// Filename    : EffectShutDown.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectShutDown.h"
#include "Gpackets/GCSystemMessage.h"
#include "Zone.h"
#include "unistd.h"
#include "signal.h"
#include "DB.h"
#include "Corpse.h"
#include "EventShutdown.h"
#include "ClientManager.h"

#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "ZoneGroupManager.h"
#include "StringPool.h"

#include <stdio.h>


//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectShutDown::EffectShutDown () 
	
{
	__BEGIN_TRY

	__END_CATCH
}

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectShutDown::EffectShutDown (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Corpse* pCorpse , Turn_t delay) 
	
: Effect(pZone,x,y,pCorpse,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectShutDown::~EffectShutDown () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectShutDown::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	affect(pCreature);

	__END_CATCH
}

//----------------------------------------------------------------------
// affect
//----------------------------------------------------------------------
void EffectShutDown::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Statement*   pStmt      = NULL;
	Result*      pResult    = NULL;
	Timeval      nextTime   = getNextTime();
	Timeval      deadLine   = getDeadline();
	Turn_t       RemainTime = deadLine.tv_sec - nextTime.tv_sec;

/*	StringStream msg;

	msg << (int)RemainTime << "초 후에 서버가 종료됩니다. 잠시 후 접속해 주시기 바랍니다. "; */
    char msg[80];
    sprintf( msg, g_pStringPool->c_str( STRID_SERVER_SHUT_DOWN_COUNT_DOWN ),
                    (int)RemainTime );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg);

	setNextTime(m_Delay);

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(ZoneGroupID) FROM ZoneGroupInfo");

		pResult->next();

		BYTE GroupCount = pResult->getInt(1) + 1;

		for (int i = 1; i < GroupCount; i++) 
		{
			ZoneGroup* pZoneGroup;

			try 
			{
				pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
			} 
			catch (NoSuchElementException&) 
			{
				SAFE_DELETE(pStmt);
				throw Error("Critical Error : ZoneInfoManager꼇닸瞳맡契삔.");
			}

			ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
			pZonePlayerManager->broadcastPacket(&gcSystemMessage);
		}

		SAFE_DELETE(pStmt);
 	}
	END_DB(pStmt)	

	/*

	ZoneInfo* pZoneInfo;

	for (int i = 1; i < 19; i++) {

		try {
	
			pZoneInfo = g_pZoneInfoManager->getZoneInfo(i);
	
		} catch (NoSuchElementException) {
			throw Error("Critical Error : ZoneInfoManager에 해당 존이 존재하지 않습니다.");
		}
	
		ZoneGroup* pZoneGroup;
		try {
	
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
	
		} catch (NoSuchElementException) {
			throw Error("Critical Error : ZoneInfoManager에 해당 존그룹이 존재하지 않습니다.");
		}

		Zone* pZone = pZoneGroup->getZone(i);
	
		pZone->broadcastPacket(&gcSystemMessage);

	}
	*/


	__END_CATCH
}
			

//----------------------------------------------------------------------
// affect to target
// 이 이펙트는 타일에 종속되지 않으므로, affect()는 호출되지 않는다.
// 왜냐하면, target은 생성자에서 지정되며, 아무런 일도 하지 않기 때문이다.
//----------------------------------------------------------------------
void EffectShutDown::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectShutDown::unaffect()
	
{
	__BEGIN_TRY

	Statement*   pStmt   = NULL;
	Result*      pResult = NULL;
//	StringStream msg;

//	msg << "서버가 종료됩니다.";

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage( g_pStringPool->getString( STRID_SERVER_SHUT_DOWN ) );

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(ZoneGroupID) FROM ZoneGroupInfo");

		pResult->next();
		BYTE GroupCount = pResult->getInt(1) + 1;

		for (int i = 1; i < GroupCount; i++) 
		{
			ZoneGroup* pZoneGroup;

			try 
			{
				pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
			} 
			catch (NoSuchElementException&) 
			{
				SAFE_DELETE(pStmt);
				throw Error("Critical Error : ZoneInfoManager꼇닸瞳맡契삔.");
			}

			ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
			pZonePlayerManager->broadcastPacket(&gcSystemMessage);
		}

		SAFE_DELETE(pStmt);
 	} 
	END_DB(pStmt)

	//kill(getpid() , 9);
	EventShutdown* pEventShutdown = new EventShutdown(NULL);
	pEventShutdown->setDeadline( 0 );

	g_pClientManager->addEvent( pEventShutdown );

	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect
//--------------------------------------------------------------------
void EffectShutDown::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectShutDown::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectShutDown::toString () const 
	
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectShutDown("
				<< "ZoneID:" << (int)m_pZone->getZoneID()
				<< ",X:"     << (int)getX()
				<< ",Y:"     << (int)getY();
	}

	if (m_pTarget)
	{
		msg << ",Target:" << m_pTarget->toString();
	}
	else
	{
		msg << ",Target:NULL";
	}

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
