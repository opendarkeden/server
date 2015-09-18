//////////////////////////////////////////////////////////////////////////////
// Filename    : PartyInvite.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Party.h"
#include "CreatureUtil.h"
#include "StringStream.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "StringStream.h"
#include "Effect.h"
#include "EffectManager.h"
#include "PCFinder.h"
#include "Item.h"
#include "PacketUtil.h"
#include "GQuestManager.h"
#include <list>

#include "VariableManager.h"

#include "skill/SkillUtil.h"
#include "skill/EffectRevealer.h"
#include "skill/EffectDetectHidden.h"
#include "skill/EffectDetectInvisibility.h"
#include "skill/EffectExpansion.h"
#include "skill/EffectActivation.h"
#include "skill/EffectGnomesWhisper.h"
#include "skill/EffectHolyArmor.h"

#include "EffectCanEnterGDRLair.h"

#include "GCPartyLeave.h"
#include "GCPartyInvite.h"
#include "GCPartyJoined.h"
#include "GCAddEffect.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCOtherModifyInfo.h"
#include "GCOtherGuildName.h"

#include <map>

//////////////////////////////////////////////////////////////////////////////
// global varible 
//////////////////////////////////////////////////////////////////////////////
GlobalPartyManager* g_pGlobalPartyManager = NULL;

//////////////////////////////////////////////////////////////////////////////
//
// class PartyInviteInfo member methods
//
//////////////////////////////////////////////////////////////////////////////

string PartyInviteInfo::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "PartyInviteInfo("
		<< "Host:" << m_HostName
		<< ",Guest:" << m_GuestName
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
// class PartyInviteInfoManager member methods
//
//////////////////////////////////////////////////////////////////////////////

PartyInviteInfoManager::PartyInviteInfoManager()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("PartyInviteInfoManager");

	__END_CATCH
}

PartyInviteInfoManager::~PartyInviteInfoManager()
	throw()
{
	__BEGIN_TRY

	map<string, PartyInviteInfo*>::iterator itr = m_InfoMap.begin();
	for (; itr != m_InfoMap.end(); itr++)
	{
		PartyInviteInfo* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}

	m_InfoMap.clear();
	
	__END_CATCH
}

bool PartyInviteInfoManager::hasInviteInfo(const string& HostName) 
	throw(Error)
{
	__BEGIN_TRY

	map<string, PartyInviteInfo*>::iterator itr = m_InfoMap.find(HostName);
	if (itr == m_InfoMap.end())
	{
		return false;
	}

	return true;

	__END_CATCH
}

bool PartyInviteInfoManager::canInvite(Creature* pHost, Creature* pGuest) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pHost != NULL && pGuest != NULL);

	// 사람끼리 초대를 해야 한다.
	if (!pHost->isPC() || !pGuest->isPC()) return false;

	// 다른 종족끼리는 초대할 수 없다.
	if (!isSameRace(pHost, pGuest)) return false;

	// 이미 누군가를 초대하고 있거나, 초대받고 있다면 초대할 수 없다.
	PartyInviteInfo* pHostInfo  = getInviteInfo(pHost->getName());
	PartyInviteInfo* pGuestInfo = getInviteInfo(pGuest->getName());
	if (pHostInfo != NULL || pGuestInfo != NULL) return false;

	// 게스트가 이미 파티에 가입되어 있다면 초대할 수 없다.
	//if (pGuest->getPartyID() != 0) return false;

	return true;

	__END_CATCH
}

bool PartyInviteInfoManager::isInviting(Creature* pHost, Creature* pGuest) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pHost != NULL && pGuest != NULL);

	PartyInviteInfo* pHostInfo  = getInviteInfo(pHost->getName());
	PartyInviteInfo* pGuestInfo = getInviteInfo(pGuest->getName());

	if (pHostInfo == NULL || pGuestInfo == NULL) return false;

	// 서로가 쌍방향으로 상대를 가리키고 있어야 한다.
	// A(Host)      | B(Guest)
	// Host  : shit | Host  : fuck
	// Guest : fuck | Guest : shit
	if ((pHostInfo->getGuestName()  == pGuestInfo->getHostName()) &&
		(pGuestInfo->getGuestName() == pHostInfo->getHostName())) return true;

	return false;

	__END_CATCH
}

void PartyInviteInfoManager::initInviteInfo(Creature* pHost, Creature* pGuest) 
	throw(Error)
{
	__BEGIN_TRY

	if (hasInviteInfo(pHost->getName()) || hasInviteInfo(pGuest->getName()))
	{
		// 여기서 무언가 중첩 현상이 일어났었다. 그러니까, CGPartyInvite
		// 패킷에 의해서 파티 초대 정보가 초기화되려는 시점인데, 이미
		// 초대 정보가 존재한다는 말이다. 원래는 에러를 던져야 하는데,
		// 원인을 알 수가 없어서, 걍 쌍방의 정보를 취소해 버리도록 변경했다.
		cancelInvite(pHost, pGuest);
		return;
	}

	PartyInviteInfo* pHostInfo  = new PartyInviteInfo;
	pHostInfo->setHostName(pHost->getName());
	pHostInfo->setGuestName(pGuest->getName());

	if (!addInviteInfo(pHostInfo))
	{
		delete pHostInfo;
	}

	PartyInviteInfo* pGuestInfo  = new PartyInviteInfo;
	pGuestInfo->setHostName(pGuest->getName());
	pGuestInfo->setGuestName(pHost->getName());

	if (!addInviteInfo(pGuestInfo))
	{
		delete pHostInfo;
	}

	__END_CATCH
}

void PartyInviteInfoManager::cancelInvite(Creature* pHost, Creature* pGuest) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pHost != NULL && pGuest != NULL);

	int nCondition = 0;

	// 둘 다 사람이 아니라면 곤란한다.
	if (!pHost->isPC() || !pGuest->isPC()) nCondition = 1;
	if (!isSameRace(pHost, pGuest))        nCondition = 2;
	if (!isInviting(pHost, pGuest))        nCondition = 4;

	if (nCondition != 0)
	{
		cerr << "PartyInviteInfoManager::cancelInvite() : Error = " << nCondition << endl;
		// initInviteInfo()에서 일어나는 현상과 마찬가지로 여기에서도 
		// 그 반대의 현상이 일어나서, 주석처리해 버렸다.
		//throw Error("PartyInviteInfoManager::cancelInvite()");
	}

	deleteInviteInfo(pHost->getName());
	deleteInviteInfo(pGuest->getName());

	__END_CATCH
}

void PartyInviteInfoManager::cancelInvite(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	PartyInviteInfo* pInfo = getInviteInfo(pCreature->getName());

	if (pInfo != NULL)
	{
		Zone* pZone = pCreature->getZone();	// if 밖에 있던걸 옮김. by sigi. 2002.5.8

		const string& HostName  = pInfo->getHostName();	// &추가. by sigi. 2002.5.8
		const string& GuestName = pInfo->getGuestName();

		Creature* pTargetCreature = NULL;
		/*
		try
		{
			pTargetCreature = pZone->getCreature(GuestName);
		}
		catch (NoSuchElementException)
		{
			pTargetCreature = NULL;
		}
		*/

		// NoSuch.. 제거. by sigi. 2002.5.2
		pTargetCreature = pZone->getCreature(GuestName);

		// 파티 초대 상대가 같은 존에 존재할 경우, 상대방에게 초대가 
		// 거부되었다는 정보를 날려준다.
		GCPartyInvite gcPartyInvite;
		gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
		gcPartyInvite.setCode(GC_PARTY_INVITE_REJECT);

		if (pTargetCreature != NULL)
		{
			Player* pTargetPlayer = pTargetCreature->getPlayer();
			Assert(pTargetPlayer != NULL);
			pTargetPlayer->sendPacket(&gcPartyInvite);
		}
		
		deleteInviteInfo(HostName);
		deleteInviteInfo(GuestName);
	}
	/*
	else
	{
		cerr << "PartyInviteInfoManager::cancelInvite() : Error" << endl;
		throw("PartyInviteInfoManager::cancelInvite() : Error");
	}
	*/

	__END_CATCH
}

bool PartyInviteInfoManager::addInviteInfo(PartyInviteInfo* pInfo) 
	throw(Error)
{
	__BEGIN_TRY

	map<string, PartyInviteInfo*>::iterator itr = m_InfoMap.find(pInfo->getHostName());
	if (itr != m_InfoMap.end())
	{
		cerr << "PartyInviteInfoManager::addInviteInfo() : DuplicatedException" << endl;
		//throw DuplicatedException("PartyInviteInfoManager::addInviteInfo() : DuplicatedException");

		// Exception제거. by sigi. 2002.5.9
		return false;
	}

	m_InfoMap[pInfo->getHostName()] = pInfo;

	return true;

	__END_CATCH
}
	
void PartyInviteInfoManager::deleteInviteInfo(const string& HostName) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	map<string, PartyInviteInfo*>::iterator itr = m_InfoMap.find(HostName);
	if (itr != m_InfoMap.end())
	{
		m_InfoMap.erase(itr);
	}

	/*
	cerr << "PartyInviteInfoManager::deleteInviteInfo() : NoSuchElementException" << endl;
	throw NoSuchElementException("PartyInviteInfoManager::deleteInviteInfo() : NoSuchElementException");
	*/

	__END_CATCH
}
	
PartyInviteInfo* PartyInviteInfoManager::getInviteInfo(const string& HostName) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	map<string, PartyInviteInfo*>::iterator itr = m_InfoMap.find(HostName);

	if (itr == m_InfoMap.end())
	{
		return NULL;
	}
	/*
	{
		cerr << "PartyInviteInfoManager::getInviteInfo() : NoSuchElementException" << endl;
		throw NoSuchElementException("PartyInviteInfoManager::getInviteInfo() : NoSuchElementException");
	}
	*/


	return itr->second;

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
//
// class Party member methods
//
//////////////////////////////////////////////////////////////////////////////

Party::Party(Creature::CreatureClass CClass) 
	throw()
{
	__BEGIN_TRY

	// 파티에 속할 수 있는 크리쳐 클래스를 정해주고...
	m_CreatureClass = CClass;

	m_bFamilyPay = false;

	// 뮤텍스에 이름을 세팅한다. (디버깅용)
	m_Mutex.setName("Party");

	__END_CATCH
}

Party::~Party() 
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_MemberMap.clear();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

// 이름으로 파티에 멤버를 찾아서 리턴한다.
Creature* Party::getMember(const string& name) const
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	//cout << "Party::getMember() : BEGIN" << endl;

	Creature* pCreature = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.find(name);
	if (itr == m_MemberMap.end())
	{
		cerr << "Party::getMember() : NoSuchElementException" << endl;
		throw NoSuchElementException("Party::getMember() : NoSuchElementException");
	}

	pCreature = itr->second;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::getMember() : END" << endl;

	return pCreature;

	__END_CATCH
}

// 멤버를 더한다.
void Party::addMember(Creature* pCreature) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	//cout << "Party::addMember() : BEGIN" << endl;

	// 파티에 속할 수 있는 종족이 아니라면...
	if (pCreature->getCreatureClass() != m_CreatureClass)
	{
		cerr << "Party::addMember() : Invalid Creature Class" << endl;
		throw Error("Party::addMember() : Invalid Creature Class");
	}

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::iterator itr = m_MemberMap.find(pCreature->getName());
	if (itr == m_MemberMap.end())
	{
		m_MemberMap[pCreature->getName()] = pCreature;
	}
	else
	{
		/*
		cerr << "Party::addMember() : DuplicatedException" << endl;
		throw DuplicatedException("Party::addMember() : DuplicatedException");
		*/
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::addMember() : END" << endl;

	__END_CATCH
}

// 파티에서 멤버를 삭제한다.
void Party::deleteMember(const string& name) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	//cout << "Party::deleteMember() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::iterator itr = m_MemberMap.find(name);
	if (itr == m_MemberMap.end())
	{
		//cerr << "Party::deleteMember() : NoSuchElementException" << endl;
		//throw NoSuchElementException("Party::deleteMember() : NoSuchElementException");

		m_Mutex.unlock();
		return;
	}

//	itr->second->removeFlag(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR);
	m_MemberMap.erase(itr);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::deleteMember() : END" << endl;

	__END_CATCH
}

// 파티에 특정 이름을 가진 멤버가 있는지 조사한다.
bool Party::hasMember(const string& name) const
	throw()
{
	__BEGIN_TRY

	//cout << "Party::hasMember() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.find(name);
	if (itr == m_MemberMap.end())
	{
		//cout << "Party::hasMember() : END" << endl;

		m_Mutex.unlock();
		return false;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::hasMember() : END" << endl;

	return true;

	__END_CATCH
}

// 글로벌 파티 매니저에서만 사용한다...
// 파티를 해체하기 전에 파티 멤버들의 파티 ID를 0으로 만들고,
// 로컬 파티 매니저에서 해당 ID를 가진 파티를 삭제한다.
void Party::destroyParty(void) 
	throw()
{
	__BEGIN_TRY

	//cout << "Party::destroyParty() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);
		pCreature->setPartyID(0);
//		pCreature->removeFlag(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR);

		//cout << "파티에 남아있는 크리쳐[" << pCreature->getName() << "]의 파티 ID를 0으로 만들었습니다." << endl;

		// 각각의 존에 있는 로컬 파티 매니저에서 해당하는 파티 객체를 삭제한다.
		Zone* pZone = pCreature->getZone();
		if (pZone != NULL)
		{
			LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
			Assert(pLocalPartyManager != NULL);
			pLocalPartyManager->deletePartyMember(m_ID, pCreature);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::destroyParty() : END" << endl;

	__END_CATCH
}

// 파티 멤버들에게 패킷을 날린다.
void Party::broadcastPacket(Packet* pPacket, Creature* pOwner) 
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	//cout << "Party::broadcastPacket() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);

		if (pCreature != pOwner) 
			pCreature->getPlayer()->sendPacket(pPacket);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::broadcastPacket() : END" << endl;

	__END_CATCH
}

// 새로운 파티원이 추가되었을 때, 파티원들에게 날아가는
// GCPartyJoined 패킷을 구성한다.
void Party::makeGCPartyJoined(GCPartyJoined* pGCPartyJoined) const
	throw()
{
	__BEGIN_TRY

	//cout << "Party::makeGCPartyJoined() : BEGIN" << endl;

	Assert(pGCPartyJoined != NULL);

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);

		PARTY_MEMBER_INFO* pInfo = new PARTY_MEMBER_INFO;

		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			pInfo->name       = pSlayer->getName();
			pInfo->sex        = pSlayer->getSex();
			pInfo->hair_style = pSlayer->getHairStyle();
			pInfo->ip         = pSlayer->getIP();
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			pInfo->name       = pVampire->getName();
			pInfo->sex        = pVampire->getSex();
			pInfo->hair_style = 0;
			pInfo->ip         = pVampire->getIP();
		}
		else if (pCreature->isOusters() )
		{
			// 아우스터스 추가. by bezz 2003.04.19
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			pInfo->name			= pOusters->getName();
			pInfo->sex			= pOusters->getSex();
			pInfo->hair_style	= 0;
			pInfo->ip			= pOusters->getIP();
		}
		else
		{
			Assert(false);
		}

		pGCPartyJoined->addMemberInfo(pInfo);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "Party::makeGCPartyJoined() : END" << endl;

	__END_CATCH
}

int Party::getSize(void) const 
	throw()
{
	__BEGIN_TRY

	return m_MemberMap.size();

	__END_CATCH
}

map<string, Creature*> Party::getMemberMap(void) throw() 
{ 
	__BEGIN_TRY

	return m_MemberMap; 

	__END_CATCH
}

int Party::getAdjacentMemberSize(Creature* pLeader) const 
	throw()
{
	__BEGIN_TRY

	//cout << "Party::getAdjacentMemberSize() : BEGIN" << endl;

	Zone* pZone = pLeader->getZone();
	Assert(pZone != NULL);

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	int rValue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);

		// 파티의 숫자에는 자신도 포함되기 때문에 
		// 같은 놈인지 다른 놈인지는 체크하지 않는다.
		Zone* pTZone = pCreature->getZone();

		// 존 포인터가 일치한다면 같은 존에 있다는 것을 의미한다.
		if (pTZone == pZone && pCreature->getDistance(cx, cy) <= 8) rValue++;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	// 자신도 포함되므로 적어도 1보다는 커야 한다.
	//Assert(rValue >= 1);
	if (rValue == 0) rValue = 1;

	//cout << "Party::getAdjacentMemberSize() : END" << endl;

	return rValue;

	__END_CATCH
}

int Party::getAdjacentMemberSize_LOCKED(Creature* pLeader) const 
	throw()
{
	__BEGIN_TRY

	//cout << "Party::getAdjacentMemberSize() : BEGIN" << endl;

	Zone* pZone = pLeader->getZone();
	Assert(pZone != NULL);

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	int rValue = 0;

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);

		// 파티의 숫자에는 자신도 포함되기 때문에 
		// 같은 놈인지 다른 놈인지는 체크하지 않는다.
		Zone* pTZone = pCreature->getZone();

		// 존 포인터가 일치한다면 같은 존에 있다는 것을 의미한다.
		if (pTZone == pZone && pCreature->getDistance(cx, cy) <= 8) rValue++;
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	// 자신도 포함되므로 적어도 1보다는 커야 한다.
	Assert(rValue >= 1);

	//cout << "Party::getAdjacentMemberSize() : END" << endl;

	return rValue;

	__END_CATCH
}

// 리더 및 파티원들의 능력치 경험치를 올린다.
// 리더의 올라간 경험치는 LeaderModifyInfo에다 집어넣고, 
// 나머지 멤버들의 올라간 경험치는 패킷을 따로 만들어 보낸다.
int Party::shareAttrExp(Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	Assert(pLeader != NULL);
	Assert(pLeader->isSlayer());

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	list<Creature*> MemberList;
	int LevelSum = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 (경험치를 올려줄) 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);

		// 로컬 파티 매니저를 통해서만 불리는 함수이기 때문에, 
		// 이 파티는 현재 로컬 파티라고 가정할 수 있다.
		// 로컬 파티 내부에서는 같은 존에 있는지를 검사할 필요가 없기 때문에
		// 거리 검사만을 한다.
		// 사실 매번 계산 때마다 이렇게 거리 계산을 한다는 것은 약간은
		// 무리가 있다고 생각하는데, 같은 존에 있으면 경험치 보너스를 받는
		// 쪽이 좋지 않을까? -- 김성민
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			//Assert(pCreature->getZone() == pLeader->getZone());

			// 어딘가에서(아마 PCManager::killCreature인거 같은데)
			// Zone이 바뀐다. -_-;
			// 찾을 시간이 없어서 일단 이렇게 간다. by sigi. 2002.5.8
			if (pCreature->getZone()==pLeader->getZone())
			{
				MemberList.push_back(pCreature);

				// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
				if (pCreature->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					LevelSum += pSlayer->getSlayerLevel();
				}
				else if (pCreature->isVampire())
				{
					// 슬레이어 파티에 뱀파이어가 있을 수 있을까?
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
					LevelSum += pVampire->getLevel();
				}
			}
		}
	}

	// 경험치를 파티원의 숫자에 증폭시킨다.
	int nMemberSize = MemberList.size();

	//cout << "파티원의 숫자 : " << nMemberSize << endl;
	//cout << "원래 경험치 : " << amount << endl;

	if (nMemberSize == 1)
	{
		m_Mutex.unlock();

		Assert(pLeader->isSlayer());
		Slayer* pLeaderSlayer = dynamic_cast<Slayer*>(pLeader);

		// 파티원이 하나라면 (근처에 다른 파티원이 없다면) 그냥 혼자 올려주고, 리턴한다.
		divideAttrExp(pLeaderSlayer, amount, 
			STRMultiplier, DEXMultiplier, INTMultiplier, 
			LeaderModifyInfo, nMemberSize);	// 파티원의 숫자

		return 0;
	}

	switch (nMemberSize)
	{
		case 2: amount = getPercentValue(amount, 150); break;
		case 3: amount = getPercentValue(amount, 195); break;
		case 4: amount = getPercentValue(amount, 225); break;
		case 5: amount = getPercentValue(amount, 250); break;
		case 6: 
			// 풀파티 경험치 이벤트
			if (g_pVariableManager->getVariable(FULL_PARTY_EXP_EVENT ) != 0 )
			{
				amount = getPercentValue(amount, 295);
			}
			else
			{
				amount = getPercentValue(amount, 270);
			}
			break;
		default: break;
	}

	//cout << "증폭된 경험치 : " << amount << endl;
	//cout << "파티원의 레벨합 : " << LevelSum << endl;

	// 각각의 파티원들의 경험치를 올려준다.
	list<Creature*>::iterator itr = MemberList.begin();
	for (; itr != MemberList.end(); itr++)
	{
		Creature* pCreature = (*itr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		int myQuota = (int)((float)amount * (float)pSlayer->getSlayerLevel() / (float)LevelSum);

		//cout << "나의 몫 : " << myQuota << endl;

		if (pCreature->getName() != pLeader->getName())
		{
			//cout << "본인[" << pCreature->getName() << "]이 아니라서 패킷을 보냅니다." << endl;

			Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pWeapon != NULL)
			{
				Item::ItemClass IClass = pWeapon->getItemClass();
				int _STR = 0, _DEX = 0, _INT = 0;
				switch (IClass)
				{
					case Item::ITEM_CLASS_SWORD:
					case Item::ITEM_CLASS_BLADE:
						_STR = 8; _DEX = 1; _INT = 1; 
						break;
					case Item::ITEM_CLASS_SG:
					case Item::ITEM_CLASS_SMG:
					case Item::ITEM_CLASS_AR:
					case Item::ITEM_CLASS_SR:
						_STR = 1; _DEX = 8; _INT = 1; 
						break;
					case Item::ITEM_CLASS_MACE: 
					case Item::ITEM_CLASS_CROSS:
						_STR = 1; _DEX = 1; _INT = 8;
						break;
					default:
						Assert(false);
						break;
				}

				// 본인이 아니라면...
				GCModifyInformation gcModifyInformation;
				divideAttrExp(pSlayer, myQuota, _STR, _DEX, _INT, 
					gcModifyInformation, nMemberSize);

				pSlayer->getPlayer()->sendPacket(&gcModifyInformation);
			}
		}
		else
		{
			//cout << "본인[" << pCreature->getName() << "]이라서 패킷 준비만 합니다." << endl;

			// 본인이라면 일단 나중에 보내기 위해, 담기만 한다.
			divideAttrExp(pSlayer, myQuota, 
				STRMultiplier, DEXMultiplier, INTMultiplier, 
				LeaderModifyInfo, nMemberSize);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return 0;

	__END_CATCH
}

int Party::shareVampireExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	Assert(pLeader != NULL);
	Assert(pLeader->isVampire());

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	list<Creature*> MemberList;
	int LevelSum = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 (경험치를 올려줄) 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);

		// 로컬 파티 매니저를 통해서만 불리는 함수이기 때문에, 
		// 이 파티는 현재 로컬 파티라고 가정할 수 있다.
		// 로컬 파티 내부에서는 같은 존에 있는지를 검사할 필요가 없기 때문에
		// 거리 검사만을 한다.
		// 사실 매번 계산 때마다 이렇게 거리 계산을 한다는 것은 약간은
		// 무리가 있다고 생각하는데, 같은 존에 있으면 경험치 보너스를 받는
		// 쪽이 좋지 않을까? -- 김성민
		// 박쥐상태에서는 파티경험치 못 먹는다. by Sequoia
		if (pCreature->getDistance(cx, cy) <= 8 && !pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT ) )
		{
			MemberList.push_back(pCreature);

			// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
			if (pCreature->isSlayer())
			{
				// 뱀파이어 파티에 슬레이어가 있을 수 있을까?
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				LevelSum += pSlayer->getSlayerLevel();
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				LevelSum += pVampire->getLevel();
			}
		}
	}

	// 경험치를 파티원의 숫자에 증폭시킨다.
	int nMemberSize = MemberList.size();

	//cout << "파티원의 숫자 : " << nMemberSize << endl;
	//cout << "원래 경험치 : " << amount << endl;

	if (nMemberSize == 1)
	{
		m_Mutex.unlock();

		Assert(pLeader->isVampire());
		Vampire* pLeaderVampire = dynamic_cast<Vampire*>(pLeader);

		// 파티원이 하나라면 (근처에 다른 파티원이 없다면) 그냥 혼자 올려주고, 리턴한다.
		increaseVampExp(pLeaderVampire, amount, LeaderModifyInfo);
		return 0;
	}

	switch (nMemberSize)
	{
		case 2: amount = getPercentValue(amount, 150); break;
		case 3: amount = getPercentValue(amount, 195); break;
		case 4: amount = getPercentValue(amount, 225); break;
		case 5: amount = getPercentValue(amount, 250); break;
		case 6:
			// 풀파티 경험치 이벤트
			if (g_pVariableManager->getVariable(FULL_PARTY_EXP_EVENT ) != 0 )
			{
				amount = getPercentValue(amount, 295);
			}
			else
			{
				amount = getPercentValue(amount, 270);
			}
			break;
		default: break;
	}

	//cout << "증폭된 경험치 : " << amount << endl;
	//cout << "파티원들의 레벨 합 : " << LevelSum << endl;

	// 각각의 파티원들의 경험치를 올려준다.
	list<Creature*>::iterator itr = MemberList.begin();
	for (; itr != MemberList.end(); itr++)
	{
		Creature* pCreature = (*itr);
		Assert(pCreature != NULL);
		Assert(pCreature->isVampire());

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		int myQuota = (int)((float)amount * (float)pVampire->getLevel() / (float)LevelSum);

		//cout << "나의 몫 : " << myQuota << endl;

		if (pCreature != pLeader)
		{
			//cout << "본인이 아니라서 패킷을 보냅니다." << endl;

			// 본인이 아니라면...
			GCModifyInformation gcModifyInformation;
			increaseVampExp(pVampire, myQuota, gcModifyInformation);
			pVampire->getPlayer()->sendPacket(&gcModifyInformation);
		}
		else
		{
			//cout << "본인이라서 패킷을 보내지 않습니다." << endl;

			// 본인이라면 일단 나중에 보내기 위해, 담기만 한다.
			increaseVampExp(pVampire, myQuota, LeaderModifyInfo);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return 0;

	__END_CATCH
}

int Party::shareOustersExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	Assert(pLeader != NULL);
	Assert(pLeader->isOusters());

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	list<Creature*> MemberList;
	int LevelSum = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 (경험치를 올려줄) 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);

		// 로컬 파티 매니저를 통해서만 불리는 함수이기 때문에, 
		// 이 파티는 현재 로컬 파티라고 가정할 수 있다.
		// 로컬 파티 내부에서는 같은 존에 있는지를 검사할 필요가 없기 때문에
		// 거리 검사만을 한다.
		// 사실 매번 계산 때마다 이렇게 거리 계산을 한다는 것은 약간은
		// 무리가 있다고 생각하는데, 같은 존에 있으면 경험치 보너스를 받는
		// 쪽이 좋지 않을까? -- 김성민
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);

			// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
			if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				LevelSum += pOusters->getLevel();
			}
		}
	}

	// 경험치를 파티원의 숫자에 증폭시킨다.
	int nMemberSize = MemberList.size();

	//cout << "파티원의 숫자 : " << nMemberSize << endl;
	//cout << "원래 경험치 : " << amount << endl;

	if (nMemberSize == 1)
	{
		m_Mutex.unlock();

		Assert(pLeader->isOusters());
		Ousters* pLeaderOusters = dynamic_cast<Ousters*>(pLeader);

		// 파티원이 하나라면 (근처에 다른 파티원이 없다면) 그냥 혼자 올려주고, 리턴한다.
		increaseOustersExp(pLeaderOusters, amount, LeaderModifyInfo);
		return 0;
	}

	switch (nMemberSize)
	{
		case 2: amount = getPercentValue(amount, 150); break;
		case 3: amount = getPercentValue(amount, 195); break;
		case 4: amount = getPercentValue(amount, 225); break;
		case 5: amount = getPercentValue(amount, 250); break;
		case 6:
			// 풀파티 경험치 이벤트
			if (g_pVariableManager->getVariable(FULL_PARTY_EXP_EVENT ) != 0 )
			{
				amount = getPercentValue(amount, 295);
			}
			else
			{
				amount = getPercentValue(amount, 270);
			}
			break;
		default: break;
	}

	// 각각의 파티원들의 경험치를 올려준다.
	list<Creature*>::iterator itr = MemberList.begin();
	for (; itr != MemberList.end(); itr++)
	{
		Creature* pCreature = (*itr);
		Assert(pCreature != NULL);
		Assert(pCreature->isOusters());

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		int myQuota = (int)((float)amount * (float)pOusters->getLevel() / (float)LevelSum);

		if (pCreature != pLeader)
		{
			//cout << "본인이 아니라서 패킷을 보냅니다." << endl;

			// 본인이 아니라면...
			GCModifyInformation gcModifyInformation;
			increaseOustersExp(pOusters, myQuota, gcModifyInformation);
			pOusters->getPlayer()->sendPacket(&gcModifyInformation);
		}
		else
		{
			//cout << "본인이라서 패킷을 보내지 않습니다." << endl;

			// 본인이라면 일단 나중에 보내기 위해, 담기만 한다.
			increaseOustersExp(pOusters, myQuota, LeaderModifyInfo);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return 0;

	__END_CATCH
}

void Party::shareRankExp(Creature* pLeader, int otherLevel) 
	throw()
{
	__BEGIN_TRY

	Assert(pLeader != NULL);
	Assert(pLeader->isPC());

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	list<Creature*> MemberList;
	int LevelSum = 0;

	int LevelSum2 = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 (경험치를 올려줄) 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);

		// 로컬 파티 매니저를 통해서만 불리는 함수이기 때문에, 
		// 이 파티는 현재 로컬 파티라고 가정할 수 있다.
		// 로컬 파티 내부에서는 같은 존에 있는지를 검사할 필요가 없기 때문에
		// 거리 검사만을 한다.
		// 사실 매번 계산 때마다 이렇게 거리 계산을 한다는 것은 약간은
		// 무리가 있다고 생각하는데, 같은 존에 있으면 경험치 보너스를 받는
		// 쪽이 좋지 않을까? -- 김성민
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);

			// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				LevelSum += pSlayer->getSlayerLevel();

				LevelSum2 += pSlayer->getHighestSkillDomainLevel();
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				LevelSum += pVampire->getLevel();

				LevelSum2 += pVampire->getLevel();
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				LevelSum += pOusters->getLevel();

				LevelSum2 += pOusters->getLevel();
			}
		}
	}

	// 경험치를 파티원의 숫자에 증폭시킨다.
	int nMemberSize = MemberList.size();

	// 파티원 평균 레벨에 의한 경험치를 구한다.
	int amount = (int) computeRankExp(LevelSum2 / nMemberSize, otherLevel);

	//cout << "파티원의 숫자 : " << nMemberSize << endl;
	//cout << "원래 경험치 : " << amount << endl;

	if (nMemberSize == 1)
	{
		m_Mutex.unlock();

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pLeader);

		// 파티원이 하나라면 (근처에 다른 파티원이 없다면) 그냥 혼자 올려주고, 리턴한다.
		pPC->increaseRankExp(amount);
		return;
	}

	switch (nMemberSize)
	{
		case 2: amount = getPercentValue(amount, 150); break;
		case 3: amount = getPercentValue(amount, 195); break;
		case 4: amount = getPercentValue(amount, 225); break;
		case 5: amount = getPercentValue(amount, 250); break;
		case 6: amount = getPercentValue(amount, 270); break;
		default: break;
	}

	//cout << "증폭된 경험치 : " << amount << endl;
	//cout << "파티원들의 레벨 합 : " << LevelSum << endl;

	// 각각의 파티원들의 경험치를 올려준다.
	list<Creature*>::iterator itr = MemberList.begin();
	for (; itr != MemberList.end(); itr++)
	{
		Creature* pCreature = (*itr);
		Assert(pCreature != NULL);

		// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
		int level = 0;
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			level = pSlayer->getSlayerLevel();

			int myQuota = amount * level / LevelSum;
			pSlayer->increaseRankExp(myQuota);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			level = pVampire->getLevel();

			int myQuota = amount * level / LevelSum;
			pVampire->increaseRankExp(myQuota);
		}
		else if (pCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			level = pOusters->getLevel();

			int myQuota = amount * level / LevelSum;
			pOusters->increaseRankExp(myQuota);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return;

	__END_CATCH
}

void Party::shareAdvancementExp(Creature* pLeader, int amount) 
	throw()
{
	__BEGIN_TRY

	Assert(pLeader != NULL);
	Assert(pLeader->isPC());

	ZoneCoord_t cx = pLeader->getX();
	ZoneCoord_t cy = pLeader->getY();

	list<Creature*> MemberList;
	int LevelSum = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 (경험치를 올려줄) 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		PlayerCreature* pCreature = dynamic_cast<PlayerCreature*>(mitr->second);
		Assert(pCreature != NULL);

		// 로컬 파티 매니저를 통해서만 불리는 함수이기 때문에, 
		// 이 파티는 현재 로컬 파티라고 가정할 수 있다.
		// 로컬 파티 내부에서는 같은 존에 있는지를 검사할 필요가 없기 때문에
		// 거리 검사만을 한다.
		// 사실 매번 계산 때마다 이렇게 거리 계산을 한다는 것은 약간은
		// 무리가 있다고 생각하는데, 같은 존에 있으면 경험치 보너스를 받는
		// 쪽이 좋지 않을까? -- 김성민
		if (pCreature->isAdvanced() && pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
			LevelSum += pCreature->getLevel() + pCreature->getAdvancementClassLevel();
		}
	}

	// 경험치를 파티원의 숫자에 증폭시킨다.
	int nMemberSize = MemberList.size();

	//cout << "파티원의 숫자 : " << nMemberSize << endl;
	//cout << "원래 경험치 : " << amount << endl;

	if (nMemberSize == 1)
	{
		m_Mutex.unlock();

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pLeader);

		// 파티원이 하나라면 (근처에 다른 파티원이 없다면) 그냥 혼자 올려주고, 리턴한다.
		if (pPC->isAdvanced() )
			pPC->increaseAdvancementClassExp(amount);
		return;
	}

	switch (nMemberSize)
	{
		case 2: amount = getPercentValue(amount, 150); break;
		case 3: amount = getPercentValue(amount, 195); break;
		case 4: amount = getPercentValue(amount, 225); break;
		case 5: amount = getPercentValue(amount, 250); break;
		case 6:
			// 풀파티 경험치 이벤트
			if (g_pVariableManager->getVariable(FULL_PARTY_EXP_EVENT ) != 0 )
			{
				amount = getPercentValue(amount, 295);
			}
			else
			{
				amount = getPercentValue(amount, 270);
			}
			break;
		default: break;
	}

	//cout << "증폭된 경험치 : " << amount << endl;
	//cout << "파티원들의 레벨 합 : " << LevelSum << endl;

	// 각각의 파티원들의 경험치를 올려준다.
	list<Creature*>::iterator itr = MemberList.begin();
	for (; itr != MemberList.end(); itr++)
	{
		PlayerCreature* pCreature = dynamic_cast<PlayerCreature*>(*itr);
		Assert(pCreature != NULL);

		// 근처에 있는 파티원 검색하는 김에 파티원들의 레벨 합도 구해둔다.
		int myQuota = amount * pCreature->getLevel() / LevelSum;
		pCreature->increaseAdvancementClassExp(myQuota);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return;

	__END_CATCH
}

void Party::shareRevealer(Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	if (!pCaster->isFlag(Effect::EFFECT_CLASS_REVEALER ) )
	{
		throw Error("Revealer 이펙트가 걸려 있지 않음");
	}

	// Caster 의 Revelaer 스킬 레벨을 가져온다
	Slayer* pSlayer = dynamic_cast<Slayer*>(pCaster);
	Assert(pSlayer != NULL);
	SkillSlot* pSkillSlot = pSlayer->getSkill(SKILL_REVEALER);
	Assert(pSkillSlot != NULL);
	ExpLevel_t ExpLevel = pSkillSlot->getExpLevel();

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			EffectRevealer* pEffectRevealer = new EffectRevealer(pSlayer);
			pEffectRevealer->setSkillLevel(ExpLevel);
			pEffectRevealer->setDeadline(Duration);
			EffectManager* pEffectManager = pSlayer->getEffectManager();
			pEffectManager->addEffect(pEffectRevealer);
			pSlayer->setFlag(Effect::EFFECT_CLASS_REVEALER);

			pZone->updateMineScan(pSlayer);
//			pZone->updateInvisibleScan(pSlayer);
			pZone->updateHiddenScan(pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_REVEALER);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Party::shareActivation(Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			EffectActivation* pEffectActivation = new EffectActivation(pSlayer);
			pEffectActivation->setDeadline(Duration);
			EffectManager* pEffectManager = pSlayer->getEffectManager();
			pEffectManager->addEffect(pEffectActivation);
			pSlayer->setFlag(Effect::EFFECT_CLASS_ACTIVATION);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ACTIVATION);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Party::shareGnomesWhisper(Creature* pCaster, int Duration, int SkillLevel )
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isOusters());

		if (pCreature != pCaster)
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
            // 이팩트 클래스를 만들어 붙인다.
			EffectGnomesWhisper* pEffect = new EffectGnomesWhisper(pOusters);
			pEffect->setDeadline(Duration);
			pEffect->setLevel(SkillLevel);
			pOusters->addEffect(pEffect);
			pOusters->setFlag(Effect::EFFECT_CLASS_GNOMES_WHISPER);

			pZone->updateDetectScan(pOusters);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pOusters->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_GNOMES_WHISPER);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Party::shareHolyArmor(Creature* pCaster, int DefBonus, int SkillLevel )
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster)
		{
			int Duration = (30 + SkillLevel/2) * 10;
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
            // 이팩트 클래스를 만들어 붙인다.
			EffectHolyArmor* pEffect = new EffectHolyArmor(pSlayer);
			pEffect->setDeadline(Duration);
			pEffect->setDefBonus(DefBonus);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_HOLY_ARMOR);

			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendModifyInfo(prev);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_HOLY_ARMOR);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
	
bool Party::shareWaterElementalHeal(Creature* pCaster, int HealPoint)
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	bool ret = false;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 13)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return false;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isOusters());

		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
		Assert(pTargetOusters != NULL);

		if (pTargetOusters != pCaster && pTargetOusters->getHP() < pTargetOusters->getHP(ATTR_MAX ) && pTargetOusters->getHP() > 0 )
		{
			ret = true;
			GCModifyInformation gcMI;
			HP_t final = min((int)pTargetOusters->getHP(ATTR_MAX), pTargetOusters->getHP() + HealPoint);
			if (final > pTargetOusters->getHP(ATTR_MAX) - pTargetOusters->getSilverDamage() )
			{
				pTargetOusters->setSilverDamage(pTargetOusters->getHP(ATTR_MAX) - final);
				gcMI.addShortData(MODIFY_SILVER_DAMAGE, pTargetOusters->getSilverDamage());
			}

			if (pTargetOusters->getHP() != final )
			{
				pTargetOusters->setHP(final);
				gcMI.addShortData(MODIFY_CURRENT_HP, final);
			}

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID(pTargetOusters->getObjectID());
			gcHP.setCurrentHP(final);

			pZone->broadcastPacket(pTargetOusters->getX(), pTargetOusters->getY(), &gcHP);
			
			pTargetOusters->getPlayer()->sendPacket(&gcMI);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pTargetOusters->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_WATER_ELEMENTAL_HEALED);
			gcAddEffect.setDuration(0);
			pZone->broadcastPacket(pTargetOusters->getX(), pTargetOusters->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return ret;

	__END_CATCH
}

void Party::shareGDRLairEnter(Creature* pLeader)
	throw(Error)
{
	__BEGIN_TRY

//	Zone*       pZone = pLeader->getZone();
	ZoneCoord_t cx    = pLeader->getX();
	ZoneCoord_t cy    = pLeader->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);

//		pCreature->setFlag(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR);
		if (!pCreature->isFlag(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR) )
		{
			EffectCanEnterGDRLair* pEffect = new EffectCanEnterGDRLair(pCreature);
			pEffect->setDeadline(216000);

			pCreature->setFlag(pEffect->getEffectClass());
			pCreature->addEffect(pEffect);

			pEffect->create(pCreature->getName());

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pCreature->getObjectID());
			gcAddEffect.setEffectID(pEffect->getSendEffectClass());
			gcAddEffect.setDuration(21600);

			pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);
		}
//			addSimpleCreatureEffect(pCreature, Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR, 216000);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Party::shareDetectHidden(Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			EffectDetectHidden* pEffectDetectHidden = new EffectDetectHidden(pSlayer);
			pEffectDetectHidden->setDeadline(Duration);
			EffectManager* pEffectManager = pSlayer->getEffectManager();
			pEffectManager->addEffect(pEffectDetectHidden);
			pSlayer->setFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN);

			pZone->updateHiddenScan(pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_DETECT_HIDDEN);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Party::shareDetectInvisibility(Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			EffectDetectInvisibility* pEffectDetectInvisibility = new EffectDetectInvisibility(pSlayer);
			pEffectDetectInvisibility->setDeadline(Duration);
			EffectManager* pEffectManager = pSlayer->getEffectManager();
			pEffectManager->addEffect(pEffectDetectInvisibility);
			pSlayer->setFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY);

			pZone->updateInvisibleScan(pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_DETECT_INVISIBILITY);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Party::shareExpansion(Creature* pCaster, int Duration, int Percent) 
	throw(Error)
{
	__BEGIN_TRY

	Zone*       pZone = pCaster->getZone();
	ZoneCoord_t cx    = pCaster->getX();
	ZoneCoord_t cy    = pCaster->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		Assert(pCreature != NULL);
		Assert(pCreature->isSlayer());

		if (pCreature != pCaster && pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			// 이미 같은 이펙트가 존재한다면 이전의 이펙트를 삭제해주어야 한다.
			if (pSlayer->isFlag(Effect::EFFECT_CLASS_EXPANSION))
			{
				pSlayer->deleteEffect(Effect::EFFECT_CLASS_EXPANSION);
			}

			EffectExpansion* pEffectExpansion = new EffectExpansion(pSlayer);
			pEffectExpansion->setDeadline(Duration);
			pEffectExpansion->setHPBonus(Percent);
			pSlayer->addEffect(pEffectExpansion);
			pSlayer->setFlag(Effect::EFFECT_CLASS_EXPANSION);

			// 이펙트를 붙였으니, 능력치를 재계산한다.
			// 그리고 본인에게 변화된 사항을 알려준다.
			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendRealWearingInfo();
			pSlayer->sendModifyInfo(prev);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_EXPANSION);
			gcAddEffect.setDuration(Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			// 아마도 최대 체력이 변경되었을 테니, HP 역시 브로드캐스팅한다.
			GCOtherModifyInfo gcOtherModifyInfo;
			makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Party::dissectCorpse(Creature* pDissecter, MonsterCorpse* pCorpse) throw(Error)
{
	__BEGIN_TRY

	//cout << __PRETTY_FUNCTION__ << endl;
	if (getSize() != 2 ) return;
	//cout << "dissectCorpse!" << endl;

	Zone*       pZone = pDissecter->getZone();
	ZoneCoord_t cx    = pDissecter->getX();
	ZoneCoord_t cy    = pDissecter->getY();

	list<Creature*> MemberList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 근처에 있는 이펙트를 걸어줄 파티원의 리스트를 가져온다.
	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature != NULL);
		if (pCreature->getDistance(cx, cy) <= 8)
		{
			MemberList.push_back(pCreature);
		}
	}

	if (MemberList.size() == 1)
	{
		m_Mutex.unlock();
		return;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	list<Creature*>::iterator litr = MemberList.begin();
	for (; litr != MemberList.end(); litr++)
	{
		Creature* pCreature = (*litr);
		if (pCreature == pDissecter ) continue;
		Assert(pCreature != NULL);
		Assert(pCreature->isPC());

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		pPC->getGQuestManager()->partyDissect(pCorpse);
	}

	__END_CATCH
}

void Party::eventPartyCrash() throw(Error)
{
	__BEGIN_TRY

	//cout << __PRETTY_FUNCTION__ << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(mitr->second);
		Assert(pPC != NULL);
		pPC->getGQuestManager()->eventPartyCrash();
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void Party::refreshFamilyPay()
{
	bool oldFamilyPay = m_bFamilyPay;
	m_bFamilyPay = false;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator mitr = m_MemberMap.begin();
	for (; mitr != m_MemberMap.end(); mitr++)
	{
		Creature* pCreature = mitr->second;
		Assert(pCreature->isPC());
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		Assert(pGamePlayer != NULL);

		if (pGamePlayer->isFamilyPayAvailable() )
		{
			m_bFamilyPay = true;
			break;
		}
	}

	// 패밀리 요금제 적용이 바뀌면 모든 파티원들에게 적용시킨다.
	// 단 패밀리 요금제 가입자는 제외한다.
	if (oldFamilyPay != m_bFamilyPay )
	{
		mitr = m_MemberMap.begin();

		for (; mitr != m_MemberMap.end(); mitr++)
		{
			Creature* pCreature = mitr->second;
			Assert(pCreature->isPC());
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
			Assert(pGamePlayer != NULL);

			if (!pGamePlayer->isFamilyPayAvailable() )
			{
				if (m_bFamilyPay )
				{
					// 패밀리 요금제 적용
					pGamePlayer->setFamilyPayPartyType(FAMILY_PAY_PARTY_TYPE_FREE_PASS);
				}
				else
				{
					// 패밀리 요금제 적용이 끝났음을 알려야한다.
					pGamePlayer->setFamilyPayPartyType(FAMILY_PAY_PARTY_TYPE_FREE_PASS_END);
				}
			}
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}

string Party::toString(void) const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Party("
		<< "ID:" << m_ID
		<< ",CClass:" << m_CreatureClass
		<< ",Member(";

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<string, Creature*>::const_iterator itr = m_MemberMap.begin();
	for (; itr != m_MemberMap.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Assert(pCreature != NULL);
		msg << pCreature->getName() << ",";
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	msg << "))";


	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//
// class PartyManager member methods
//
//////////////////////////////////////////////////////////////////////////////

PartyManager::PartyManager()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("PartyManager");

	__END_CATCH
}

PartyManager::~PartyManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

bool PartyManager::createParty(int ID, Creature::CreatureClass CClass) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 중첩되는 파티를 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(ID);
	if (itr != m_PartyMap.end())
	{
		m_Mutex.unlock();
		return false;
	}

	Party* pParty = new Party(CClass);
	pParty->setID(ID);

	m_PartyMap[ID] = pParty;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}

Party* PartyManager::getParty(int ID) 	// by sigi. 2002.10.14
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		return NULL;
	}

	return itr->second;
	
	__END_CATCH
}


bool PartyManager::addPartyMember(int ID, Creature* pCreature) 
	throw(NoSuchElementException, DuplicatedException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		// 없다면 여기서 생성해준다.
		Party* pNewParty = new Party(pCreature->getCreatureClass());
		pNewParty->setID(ID);

		m_PartyMap[ID] = pNewParty;

		// 의미가 있는 체크일까...-_-
		if (pNewParty->getSize() >= PARTY_MAX_SIZE)
		{
			m_Mutex.unlock();
			return false;
		}

		pNewParty->addMember(pCreature);
	}
	else
	{
		Party* pParty = itr->second;
		Assert(pParty != NULL);

		if (pParty->getSize() >= PARTY_MAX_SIZE)
		{
			m_Mutex.unlock();
			return false;
		}

		pParty->addMember(pCreature);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}

bool PartyManager::deletePartyMember(int ID, Creature* pCreature) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return false;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->deleteMember(pCreature->getName());

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
// class LocalPartyManager member methods
//
//////////////////////////////////////////////////////////////////////////////

LocalPartyManager::LocalPartyManager()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("LocalPartyManager");

	__END_CATCH
}

LocalPartyManager::~LocalPartyManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void LocalPartyManager::heartbeat(void)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	map<int, Party*>::iterator before  = m_PartyMap.end();
	map<int, Party*>::iterator current = m_PartyMap.begin(); 
	
	while (current != m_PartyMap.end()) 
	{
		Party* pParty = current->second;
		Assert(pParty != NULL);

		if (pParty->getSize() == 0)
		{
			//cout << "로컬파티의 사이즈가 0이 되어서, 파티 객체[" << pParty->getID() << "]를 삭제합니다." << endl;

			SAFE_DELETE(pParty);

			m_PartyMap.erase(current);

			if (before == m_PartyMap.end()) 	// first element
			{
				current = m_PartyMap.begin();
			}
			else // !first element
			{
				current = before;
				current ++;
			}
		}
		else
		{
			before = current ++;
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

int LocalPartyManager::getAdjacentMemberSize(int PartyID, Creature* pLeader) const 
	throw()
{
	__BEGIN_TRY

	int size = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	size = pParty->getAdjacentMemberSize(pLeader);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return size;

	__END_CATCH
}

int LocalPartyManager::shareAttrExp(int PartyID, Creature* pLeader, int amount, 
		int STRMultiplier, int DEXMultiplier, int INTMultiplier, 
		ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	int rvalue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	rvalue = pParty->shareAttrExp(pLeader, amount, STRMultiplier, DEXMultiplier, INTMultiplier, LeaderModifyInfo);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return rvalue;

	__END_CATCH
}

int LocalPartyManager::shareVampireExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	int rvalue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	rvalue = pParty->shareVampireExp(pLeader, amount, LeaderModifyInfo);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return rvalue;

	__END_CATCH
}

int LocalPartyManager::shareOustersExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const 
	throw()
{
	__BEGIN_TRY

	int rvalue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	rvalue = pParty->shareOustersExp(pLeader, amount, LeaderModifyInfo);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return rvalue;

	__END_CATCH
}

int LocalPartyManager::shareRankExp(int PartyID, Creature* pLeader, int amount) const 
	throw()
{
	__BEGIN_TRY

	//int rvalue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareRankExp(pLeader, amount);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return 0;

	__END_CATCH
}

void LocalPartyManager::shareRevealer(int PartyID, Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareRevealer(pCaster, Duration);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareDetectHidden(int PartyID, Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareDetectHidden(pCaster, Duration);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareDetectInvisibility(int PartyID, Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareDetectInvisibility(pCaster, Duration);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareExpansion(int PartyID, Creature* pCaster, int Duration, int percent) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareExpansion(pCaster, Duration, percent);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareActivation(int PartyID, Creature* pCaster, int Duration) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareActivation(pCaster, Duration);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareGnomesWhisper(int PartyID, Creature* pCaster, int Duration, int SkillLevel)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareGnomesWhisper(pCaster, Duration, SkillLevel);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

void LocalPartyManager::shareHolyArmor(int PartyID, Creature* pCaster, int DefBonus, int SkillLevel)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareHolyArmor(pCaster, DefBonus, SkillLevel);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

bool LocalPartyManager::shareWaterElementalHeal(int PartyID, Creature* pCaster, int HealPoint)
	throw(Error)
{
	__BEGIN_TRY

	bool ret = false;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return false;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	ret = pParty->shareWaterElementalHeal(pCaster, HealPoint);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return ret;

	__END_CATCH
}

void LocalPartyManager::shareGDRLairEnter(int PartyID, Creature* pLeader)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareGDRLairEnter(pLeader);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	__END_CATCH
}

int LocalPartyManager::shareAdvancementExp(int PartyID, Creature* pLeader, int amount) const throw()
{
	__BEGIN_TRY

	//int rvalue = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex);

	// 해당하는 파티가 있는지 찾아본다.
	map<int, Party*>::const_iterator itr = m_PartyMap.find(PartyID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return 0;
	}

	Party* pParty = itr->second;
	Assert(pParty != NULL);

	pParty->shareAdvancementExp(pLeader, amount);

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	return 0;

	__END_CATCH
}

string LocalPartyManager::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LocalPartyManager(";

	__ENTER_CRITICAL_SECTION(m_Mutex);

	map<int, Party*>::const_iterator itr = m_PartyMap.begin();
	for (; itr != m_PartyMap.end(); itr++)
	{
		Party* pParty = itr->second;
		Assert(pParty != NULL);
		msg << pParty->toString() << ",";
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex);

	msg << ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//
// class GlobalPartyManager member methods
//
//////////////////////////////////////////////////////////////////////////////

GlobalPartyManager::GlobalPartyManager()
	throw()
{
	__BEGIN_TRY

	m_PartyIDRegistry = 0;
	m_Mutex.setName("GlobalPartyManager");

	__END_CATCH
}

GlobalPartyManager::~GlobalPartyManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

bool GlobalPartyManager::canAddMember(int ID) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<int, Party*>::iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();
		return false;
	}

	Party* pParty = itr->second;

	if (pParty->getSize() >= PARTY_MAX_SIZE)
	{
		m_Mutex.unlock();
		return false;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}

bool GlobalPartyManager::addPartyMember(int ID, Creature* pCreature) 
	throw(NoSuchElementException, DuplicatedException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//cout << "GlobalPartyManager::addPartyMember() : BEGIN" << endl;

	// 먼저 해당파티를 찾아서 피티원의 숫자를 확인한다.
	map<int, Party*>::iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		m_Mutex.unlock();

		//cerr << "GlobalPartyManager::addPartyMember() : NoSuchElementException" << endl;
		//throw NoSuchElementException("GlobalPartyManager::addPartyMember() : NoSuchElementException");

		// NoSuch제거. by sigi. 2002.5.13
		return false;
	}

	Party* pParty = itr->second;

	if (pParty->getSize() >= PARTY_MAX_SIZE)
	{
		m_Mutex.unlock();

		//cout << "파티 맥스 사이즈를 초과" << endl;
		//cout << "GlobalPartyManager::addPartyMember() : END" << endl;
		return false;
	}

	if (pParty->getSize() == 2 )
	{
		pParty->eventPartyCrash();
	}

	// 파티원을 추가한다.
	pParty->addMember(pCreature);
	pCreature->setPartyID(pParty->getID());

	// 다른 멤버들에게 파티원이 추가되었다는 사실을 알려준다.
	// 최초에 2명이 파티를 구성할 경우, 1명을 더한 다음에 그 사람에게
	// 한명 이름만이 들어가 있는 파티 리스트가 날아가게 된다.
	// 그 다음 2번째 멤버가 들어가면 2명에게 2명이 들어가 있는 리스트가 
	// 차례로 날아가게 된다.
	// 그러므로 파티원이 1명일 때는 보내지 않아야, 파티 리스트가 2번
	// 날아가는 것을 방지할 수 있다.
	if (pParty->getSize() != 1)
	{
		GCPartyJoined gcPartyJoined;
		pParty->makeGCPartyJoined(&gcPartyJoined);
		pParty->broadcastPacket(&gcPartyJoined);

		map<string, Creature*> memberMap = pParty->getMemberMap();
		map<string, Creature*>::iterator itr = memberMap.begin();
		GCOtherGuildName gcOtherGuildName;

		for (; itr != memberMap.end() ; ++itr )
		{
			Creature* pTargetCreature = itr->second;
			if (pTargetCreature != NULL && pTargetCreature->isPC() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);

				if (pPC != NULL && pPC->getGuildID() != pPC->getCommonGuildID() )
				{
					gcOtherGuildName.setObjectID(pPC->getObjectID());
					gcOtherGuildName.setGuildID(pPC->getGuildID());
					gcOtherGuildName.setGuildName(pPC->getGuildName());

					pParty->broadcastPacket(&gcOtherGuildName);
				}
			}
		}
	}

	// 패밀리 요금제 적용 처리
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	if (pGamePlayer != NULL )
	{
		if (pParty->isFamilyPay() && !pGamePlayer->isFamilyPayAvailable() )
		{
			// 패밀리 요금제 적용 파티라면 유료존 출입권을 준다.
			pGamePlayer->setFamilyPayPartyType(FAMILY_PAY_PARTY_TYPE_FREE_PASS);
		}
		else if (pGamePlayer->isFamilyPayAvailable() )
		{
			// 패밀리 요금제인 파티원이 참가하게 될 경우 파티를 패밀리 요금제 적용 파티로 만든다.
			pParty->refreshFamilyPay();
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "GlobalPartyManager::addPartyMember() : END" << endl;

	return true;

	__END_CATCH
}

bool GlobalPartyManager::deletePartyMember(int ID, Creature* pCreature) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	//cout << "GlobalPartyManager::deletePartyMember() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<int, Party*>::iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		//m_Mutex.unlock();

		cerr << "GlobalPartyManager::deletePartyMember() : NoSuchElementException" << endl;
		//throw NoSuchElementException("GlobalPartyManager::deletePartyMember() : NoSuchElementException");

		// 외부에서 NoSuch처리도 안하는데 -_-; by sigi. 2002.5.9
		m_Mutex.unlock();
		return false;
	}

	Party* pParty = itr->second;

	//cout << "파티를 찾았다." << endl;
	//cout << pParty->toString() << endl;
	//cout << "지우려고하는 놈의 이름은:" << pCreature->getName() << endl;

	// 멤버들에게 파티원이 파티에서 추방되었다는 사실을 알려준다.
	GCPartyLeave gcPartyLeave;
	gcPartyLeave.setExpellee(pCreature->getName());
	gcPartyLeave.setExpeller("");
	pParty->broadcastPacket(&gcPartyLeave);

	pParty->eventPartyCrash();

	// 떠나는 당사자에게도 GCPartyLeave가 날아가야하기 때문에,
	// 먼저 패킷을 브로드캐스팅한 다음에, 실제로 파티에서 삭제해준다.
	pParty->deleteMember(pCreature->getName());
	pCreature->setPartyID(0);

	// 패밀리 요금제 적용 처리
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	if (pGamePlayer != NULL )
	{
		if (pGamePlayer->isFamilyPayAvailable() )
		{
			// 패밀리 요금제인 파티원이 떠나하게 될 경우 패밀리 요금제 적용을 새로 계산한다.
			pParty->refreshFamilyPay();
		}
		else if (pParty->isFamilyPay() )
		{
			// 패밀리 요금제 적용 파티일 경우 패밀리 적용을 끝낸다.
			pGamePlayer->setFamilyPayPartyType(FAMILY_PAY_PARTY_TYPE_FREE_PASS_END);
		}
	}

	// 파티의 사이즈가 1이 되었다면 삭제한다.
	if (pParty->getSize() == 1)
	{
		//cout << "글로벌파티의 사이즈가 0이 되어서, 파티 객체[" << pParty->getID() << "]를 삭제합니다." << endl;

		m_PartyMap.erase(itr);

		// 남은 파티원들의 파티 ID를 0으로 만들고,
		// 각각의 로컬 파티 매니저에서 파티를 삭제한다.
		pParty->destroyParty();

		// 객체를 지운다.
		SAFE_DELETE(pParty);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "GlobalPartyManager::deletePartyMember() : END" << endl;

	return true;

	__END_CATCH
}

bool GlobalPartyManager::expelPartyMember(int ID, Creature* pExpeller, const string& ExpelleeName) 
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	//cout << "GlobalPartyManager::expelPartyMember() : BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 먼저 해당파티를 찾는다.
	map<int, Party*>::iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		cerr << "GlobalPartyManager::expelPartyMember() : NoSuchElementException" << endl;

		// 외부에서 NoSuch처리도 안하는데 -_-; by sigi. 2002.5.9
		//throw NoSuchElementException("GlobalPartyManager::expelPartyMember() : NoSuchElementException");

		m_Mutex.unlock();
		return false;
	}

	Party* pParty = itr->second;

	// 추방하는 놈이 이 파티에 있는지 검사해야 한다.
	if (!pParty->hasMember(pExpeller->getName()))
	{
		m_Mutex.unlock();

		// 에러인데...?
		//cout << "추방하는 놈이 파티에 존재하지 않음" << endl;
		//cout << "GlobalPartyManager::expelPartyMember() : END" << endl;
		return false;
	}

	// 추방당할 놈이 파티에 존재하는지를 체크해야 한다.
	if (!pParty->hasMember(ExpelleeName))
	{
		m_Mutex.unlock();

		// 에러인데...?
		//cout << "추방당하는 놈이 파티에 존재하지 않음" << endl;
		//cout << "GlobalPartyManager::expelPartyMember() : END" << endl;
		return false;
	}

	// 멤버들에게 파티원이 파티에서 추방되었다는 사실을 알려준다.
	GCPartyLeave gcPartyLeave;
	gcPartyLeave.setExpellee(ExpelleeName);
	gcPartyLeave.setExpeller(pExpeller->getName());
	pParty->broadcastPacket(&gcPartyLeave);

	pParty->eventPartyCrash();

	//cout << "멤버들에게 파티원이 파티에서 추방되었다는 사실을 알려준다." << endl;

	// 추방당할 놈을 파티에서 삭제한다.
	// * NOTE *
	// 파티에서 먼저 삭제하지 않고, 패킷을 보낸 다음에 삭제하는 이유는
	// 추방당한 놈에게 가는 패킷이나, 다른 멤버들에게 추방되었다고 알려주는
	// 패킷이나 같은 패킷을 쓰기 때문이다. 
	Creature* pExpellee = pParty->getMember(ExpelleeName);
	pExpellee->setPartyID(0);
	pParty->deleteMember(ExpelleeName);

	// 패밀리 요금제 적용 처리
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pExpellee->getPlayer());
	if (pGamePlayer != NULL )
	{
		if (pGamePlayer->isFamilyPayAvailable() )
		{
			// 패밀리 요금제인 파티원이 떠나하게 될 경우 패밀리 요금제 적용을 새로 계산한다.
			pParty->refreshFamilyPay();
		}
		else if (pParty->isFamilyPay() )
		{
			// 패밀리 요금제 적용 파티일 경우 패밀리 적용을 끝낸다.
			pGamePlayer->setFamilyPayPartyType(FAMILY_PAY_PARTY_TYPE_FREE_PASS_END);
		}
	}

	//cout << "파티에서 [" << pExpellee->getName() << "]를 삭제했다." << endl;

	// 파티의 사이즈가 1이 되었다면 삭제한다.
	if (pParty->getSize() == 1)
	{
		//cout << "파티 사이즈가 1이 되어서 파티를 삭제한다." << endl;

		m_PartyMap.erase(itr);

		//cout << "itr을 삭제" << endl;

		// 남은 파티원들의 파티 ID를 0으로 만들고,
		// 각각의 로컬 파티 매니저에서 파티를 삭제한다.
		pParty->destroyParty();

		//cout << "After Party::destroyParty()" << endl;

		// 객체를 지운다.
		SAFE_DELETE(pParty);

		//cout << "After object deletion" << endl;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	//cout << "GlobalPartyManager::expelPartyMember() : END" << endl;

	return true;

	__END_CATCH
}

void GlobalPartyManager::refreshFamilyPay(int ID )
{
	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 먼저 해당파티를 찾는다.
	map<int, Party*>::iterator itr = m_PartyMap.find(ID);
	if (itr == m_PartyMap.end())
	{
		cerr << "GlobalPartyManager::refreshFamilyPay() : NoSuchElementException" << endl;

		m_Mutex.unlock();
		return;
	}

	Party* pParty = itr->second;

	pParty->refreshFamilyPay();

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}

int GlobalPartyManager::registerParty(void) 
	throw(Error)
{
	__BEGIN_TRY

	int PartyID = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	PartyID = ++m_PartyIDRegistry;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return PartyID;

	__END_CATCH
}

string GlobalPartyManager::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GlobalPartyManager(";

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map<int, Party*>::const_iterator itr = m_PartyMap.begin();
	for (; itr != m_PartyMap.end(); itr++)
	{
		Party* pParty = itr->second;
		Assert(pParty != NULL);
		msg << pParty->toString() << ",";
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	msg << ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
// 편의를 위한 전역 함수들...
//
//////////////////////////////////////////////////////////////////////////////
void deleteAllPartyInfo(Creature* pCreature)
	throw()
{
	__BEGIN_TRY

	//cout << "DeleteAllPartyInfo BEGIN" << endl;

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
	Assert(pPIIM != NULL);

	// 클래스가 삭제될 경우, 해당하는 파티 초청 정보를 삭제해야 함은 물론,
	// 파티 초청 상대에게도 이 사실을 알려줘야 한다.
	PartyInviteInfo* pInviteInfo = pPIIM->getInviteInfo(pCreature->getName());
	if (pInviteInfo != NULL)
	{
		pPIIM->cancelInvite(pCreature);
	}

	int PartyID = pCreature->getPartyID();

	// 파티에 속해있을 경우에는 파티에서 자신을 삭제하고, 
	// 다른 파티원들에게 알려야 한다.
	if (PartyID != 0)
	{
		// 글로벌 파티에서 삭제하고, 파티원들에게 알린다.
		g_pGlobalPartyManager->deletePartyMember(PartyID, pCreature);

		// 현재 속해있는 존의 로컬파티매니저에서 정보를 삭제한다.
		// Zone::deleteCreature() 함수 내부에서 특정 크리쳐가 
		// 그 존을 떠날 경우, LocalPartyManager 내부에서 그 크리쳐가
		// 속한 파티에서 크리쳐를 지워주므로, 여기서 지워줄 필요가 없다.
		//
		// 어디인지는 정확하게 알 수는 없으나, 어디에선가 로컬 파티에서
		// 포인터를 확실히 지워주지 않는 현상이 발생하는 듯 하다.
		// 그래서 원래 주석처리했던 부분이었으나, 다시 주석처리를 제거한다.
		// -- 2002.01.08 김성민
		Zone* pZone = pCreature->getZone();
		if (pZone != NULL)
		{
			// 로컬 파티에서 삭제한다.
			LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
			Assert(pLocalPartyManager != NULL);
			pLocalPartyManager->deletePartyMember(PartyID, pCreature);
		}

		// 글로벌 파티 내부에서 파티 ID를 0으로 만들지만,
		// 확실하게 해주는 의미에서 다시한번 0으로 만들어준다.
		pCreature->setPartyID(0);
	}

	//cout << "DeleteAllPartyInfo END" << endl;

	__END_CATCH
}
