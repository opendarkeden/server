//////////////////////////////////////////////////////////////////////////////
// Filename    : PCFinder.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PCFinder.h"
#include "Player.h"
#include "PlayerCreature.h"
//#include "GamePlayer.h"

//////////////////////////////////////////////////////////////////////////////
// class PCFinder member methods
//////////////////////////////////////////////////////////////////////////////

PCFinder::PCFinder()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("PCFinder");

	__END_CATCH
}

PCFinder::~PCFinder()
	throw()
{
	__BEGIN_TRY

	m_PCs.clear();

	__END_CATCH
}

// add creature to hash_map
// execute just once at PC's login
void PCFinder::addCreature (Creature* pCreature) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert(pCreature != NULL);

	const string& Name = pCreature->getName();
	const string& ID = pCreature->getPlayer()->getID();

	hash_map< string , Creature* >::iterator itr = m_PCs.find(Name);
	hash_map< string , Creature* >::iterator itr2 = m_IDs.find(ID); // for BillingServer. by sigi. 2002.11.18

	if (itr != m_PCs.end() 
		|| itr2 != m_IDs.end())
	{
		//m_Mutex.unlock();
		throw DuplicatedException();
	}

	m_PCs[ Name ]	= pCreature;
	m_IDs[ ID ] 	= pCreature; // for BillingServer. by sigi. 2002.11.18

	if ( pCreature->isPC() )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
//		m_GuildMap.insert( pair<GuildID_t, Creature*>( pPC->getGuildID(), pCreature ) );
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

// Delete creature from hash_map
// execute just once at PC's logout
void PCFinder::deleteCreature (const string & name) 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< string , Creature* >::iterator itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		//cerr << "PCFinder::deleteCreature() : NoSuchElementException" << endl;
		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2

		m_Mutex.unlock();
		return;
	}


	// for BillingServer. by sigi. 2002.11.18
	Creature* pCreature = itr->second;
	Player* pPlayer = pCreature->getPlayer();
	Assert(pPlayer!=NULL);

	const string& ID = pPlayer->getID();

	hash_map< string , Creature* >::iterator itr2 = m_IDs.find(ID);

	if (itr != m_IDs.end())
	{
		m_IDs.erase(itr2);
	}
	// 요기까지 2002.11.18

/*	if ( pCreature->isPC() )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		pair<multimap< GuildID_t, Creature* >::iterator, multimap< GuildID_t, Creature* >::iterator> range = m_GuildMap.equal_range( pPC->getGuildID() );
		for ( multimap<GuildID_t, Creature*>::iterator itr = range.first ; itr != range.second ; ++itr )
		{
			if ( itr->second == pCreature )
			{
				m_GuildMap.erase( itr );
				break;
			}
		}
	}*/

	m_PCs.erase(itr);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

// get creature with PC-name
Creature* PCFinder::getCreature_LOCKED (const string & name) const 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		//cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//cerr << "PCFinder::getCreature() : NoSuchCreature" << endl;
		//m_Mutex.unlock();

		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2
		return NULL;
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	return itr->second;


	__END_CATCH
}

// get creature with PlayerID
Creature* PCFinder::getCreatureByID_LOCKED (const string & ID) const 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_IDs.find(ID);

	if (itr == m_IDs.end())
	{
		//cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//cerr << "PCFinder::getCreature() : NoSuchCreature" << endl;
		//m_Mutex.unlock();

		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2
		return NULL;
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	return itr->second;


	__END_CATCH
}



// get creature with PC-name
Creature* PCFinder::getCreature (const string & name) const 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		//cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//cerr << "PCFinder::getCreature() : NoSuchCreature" << endl;
		m_Mutex.unlock();

		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2
		return NULL;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return itr->second;


	__END_CATCH
}

// get creature with PlayerID
Creature* PCFinder::getCreatureByID (const string & ID) const 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_IDs.find(ID);

	if (itr == m_IDs.end())
	{
		//cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//cerr << "PCFinder::getCreature() : NoSuchCreature" << endl;
		m_Mutex.unlock();

		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2
		return NULL;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return itr->second;


	__END_CATCH
}

// get creature's IP address 
IP_t PCFinder::getIP (const string & name) const 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	IP_t IP = 0;

	hash_map< string , Creature* >::const_iterator itr;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//m_Mutex.unlock();
		throw NoSuchElementException();
	}

	Creature* pCreature = itr->second;
	Assert( pCreature->isPC() );

	Player* pPlayer = pCreature->getPlayer();
	Assert( pPlayer != NULL );

	Socket* pSocket = pPlayer->getSocket();
	Assert( pSocket != NULL );

	IP = pSocket->getHostIP();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return IP;

	__END_CATCH
}

list<Creature*> PCFinder::getGuildCreatures(GuildID_t gID, uint Num)
{
	hash_map<string, Creature*>::iterator itr = m_PCs.begin();
	list<Creature*> ret;

	for ( uint i=0 ; itr != m_PCs.end() && i < Num ; ++itr, ++i )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
		if ( pPC != NULL && pPC->getGuildID() == gID ) ret.push_back( pPC );
	}

	return ret;
}

/*
// get creature with PC-name
bool PCFinder::sendPacket (const string& name, Packet* pPacket) const
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		m_Mutex.unlock();

		return false;
	}

	// sendPacket
	try {
		Creature* pCreature = itr->second;
		Player* pPlayer = pCreature->getPlayer();
		pPlayer->sendPacket( pPacket );
	} catch (Throwable& ) {
		// 그냥 무시한다.
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH

	return true;
}

// kick
bool PCFinder::setKickCharacter (const string & name, const string& host, uint port) const 
	throw ()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map< string , Creature* >::const_iterator itr;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	itr = m_PCs.find(name);

	if (itr == m_PCs.end())
	{
		//cerr << "PCFinder::getCreature() : NoSuchElementException" << endl;
		//cerr << "PCFinder::getCreature() : NoSuchCreature" << endl;
		m_Mutex.unlock();

		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.2
		return false;
	}

	Creature* pCreature = itr->second;
	Player* pPlayer = pCreature->getPlayer();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>( pPlayer );
	Assert(pGamePlayer!=NULL);

	// 강제 종료 시킨다.
	pGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
	pGamePlayer->setKickForLogin(true);

	// 접속 해제 후, 응답을 보내줄 곳..
	pGamePlayer->setKickRequestHost( host );
	pGamePlayer->setKickRequestPort( port );


	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH

	return true;
}
*/

void PCFinder::addNPC(NPC *pNPC) throw(DuplicatedException, Error)
{
    __BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

    Assert(pNPC != NULL);

    const string& Name = pNPC->getName();

    hash_map< string , NPC* >::iterator itr = m_NPCs.find(Name);

    if (itr != m_NPCs.end())
    {
		return;
        //throw DuplicatedException();
    }

    m_NPCs[ Name ] = pNPC;

    __LEAVE_CRITICAL_SECTION(m_Mutex)

    __END_CATCH
}


void PCFinder::deleteNPC (const string & name)
    throw ()
{

    // 실제로 사용 안 할 함수라고 생각함 그래도 그냥 add 랑 쌍을 맞추기 위해 =_=
    __BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

    hash_map< string , NPC* >::iterator itr = m_NPCs.find(name);

    if (itr == m_NPCs.end())
    {
        return;
    }

    m_NPCs.erase(itr);

    __LEAVE_CRITICAL_SECTION(m_Mutex)

    __END_CATCH
}


NPC* PCFinder::getNPC (const string & name) const
    throw ()
{
    __BEGIN_TRY

    hash_map< string , NPC* >::const_iterator itr;

    __ENTER_CRITICAL_SECTION(m_Mutex)

    itr = m_NPCs.find(name);

    if (itr == m_NPCs.end())
    {
        m_Mutex.unlock();
        return NULL;
    }

    __LEAVE_CRITICAL_SECTION(m_Mutex)

    return itr->second;


    __END_CATCH
}


NPC* PCFinder::getNPC_LOCKED (const string & name) const
    throw ()
{
    __BEGIN_TRY

    hash_map< string , NPC* >::const_iterator itr;

    itr = m_NPCs.find(name);

    if (itr == m_NPCs.end())
    {
        return NULL;
    }

    return itr->second;

    __END_CATCH
}

// global variable definition
PCFinder* g_pPCFinder = NULL;
