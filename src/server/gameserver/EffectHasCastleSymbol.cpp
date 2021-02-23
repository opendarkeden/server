//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasCastleSymbol.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasCastleSymbol.h"
#include "ZoneUtil.h"
#include "Creature.h"
#include "Slayer.h"
#include "CastleSymbol.h"
#include "CastleInfoManager.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "WarSystem.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "GuildManager.h"
#include "StringPool.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

const Effect::EffectClass EffectHasCastleSymbol::EffectClasses[6] =
{
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_2,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_3,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_4,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_5,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_6,
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasCastleSymbol::EffectHasCastleSymbol(Creature* pCreature)
	throw(Error)
: EffectHasRelic( pCreature )
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasCastleSymbol::EffectHasCastleSymbol(Item* pItem)
	throw(Error)
: EffectHasRelic( pItem )
{
	__BEGIN_TRY

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasCastleSymbol::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// 존 정보를 얻는다.
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
	Assert( pZoneInfo != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC!=NULL);
	
	// 위치를 알린다.
/*	StringStream msg;
	msg << pCreature->getName() << " 님(" 
		//<< ( pCreature->isSlayer() ? "슬레이어" : "뱀파이어" ) << ")이 " 
		<< g_pGuildManager->getGuildName( pPC->getGuildID() ) << ")이 "
	    << pZoneInfo->getFullName() << "(" << (int)pCreature->getX() << ", " << (int)pCreature->getY()
		<< ")에서 성의 상징(" << m_PartName << ")을 가지고 있습니다.";
	*/

	char msg[300]; 
	sprintf( msg, g_pStringPool->c_str( STRID_BROADCAST_CASTLE_SYMBOL_POSITION ),
					pCreature->getName().c_str(), g_pGuildManager->getGuildName( pPC->getGuildID() ).c_str(),
					pZoneInfo->getFullName().c_str(), (int)pCreature->getX(), (int)pCreature->getY(),
					m_PartName.c_str() );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg);

	
	g_pCastleInfoManager->broadcastShrinePacket( m_Part , &gcSystemMessage );
/*
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_Part );
	
	const list<ZoneID_t>& ZoneIDList = pCastleInfo->getZoneIDList();
	list<ZoneID_t>::const_iterator itr = ZoneIDList.begin();

	for ( ; itr != ZoneIDList.end() ; itr++) 
	{
		Zone* pCastleZone = getZoneByZoneID( *itr );
		pCastleZone->broadcastPacket( &gcSystemMessage );
	}
*/
//	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	setNextTime(m_Tick);
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasCastleSymbol::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	if (m_pZone==NULL) return;

	// 성에 전쟁이 진행중인 경우만 메세지를 보내준다.
	ZoneID_t 	castleZoneID;
	bool		isCastle;

	isCastle = g_pCastleInfoManager->getCastleZoneID( m_pZone->getZoneID() , castleZoneID);

	if ( isCastle && g_pWarSystem->hasCastleActiveWar( castleZoneID ))
	{
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		// 위치를 알린다.
/*		StringStream msg;
		msg << pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y
			<< ")의 성단에 " << m_PartName << " 성의 상징 이 있습니다.";
*/

		char msg[200];
		sprintf( msg, g_pStringPool->c_str( STRID_BROADCAST_CASTLE_SYMBOL_POSITION_2 ),
						pZoneInfo->getFullName().c_str(), (int)m_X, (int)m_Y, m_PartName.c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);

		g_pCastleInfoManager->broadcastShrinePacket( m_Part , &gcSystemMessage );
/*
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_Part );
		
		const list<ZoneID_t>& ZoneIDList = pCastleInfo->getZoneIDList();
		list<ZoneID_t>::const_iterator itr = ZoneIDList.begin();

		for ( ; itr != ZoneIDList.end() ; itr++) 
		{
			Zone* pCastleZone = getZoneByZoneID( *itr );
			pCastleZone->broadcastPacket( &gcSystemMessage );
		}
*/
//		g_pZoneGroupManager->broadcast( &gcSystemMessage );

	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectHasCastleSymbol::setPart( int part )
	throw()
{
	__BEGIN_TRY

	const CastleSymbolInfo* pCastleSymbolInfo = dynamic_cast<const CastleSymbolInfo*>(g_pCastleSymbolInfoManager->getItemInfo( part ) );

	if ( pCastleSymbolInfo != NULL )
	{
		m_Part = part;
		m_PartName = pCastleSymbolInfo->getName();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasCastleSymbol::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasCastleSymbol("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
