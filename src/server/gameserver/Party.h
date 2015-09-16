//////////////////////////////////////////////////////////////////////////////
// Filename    : Party.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PARTY_H__
#define __PARTY_H__

#include "Creature.h"
#include "Mutex.h"
#include "ModifyInfo.h"
#include "Mutex.h"
#include <map>
#include <list>

// 파티의 최대 크기
const int PARTY_MAX_SIZE = 6;

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Packet;
class GCPartyJoined;
class Creature;
class MonsterCorpse;

//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfo
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfo
{
public:
	PartyInviteInfo() { m_HostName = ""; m_GuestName = ""; }
	~PartyInviteInfo() {}

public:
	string getHostName(void) const { return m_HostName; }
	void setHostName(const string& name) { m_HostName = name; }

	string getGuestName(void) const { return m_GuestName; }
	void setGuestName(const string& name) { m_GuestName = name; }

public:
	string toString(void) const throw();

protected:
	string m_HostName;
	string m_GuestName;
};


//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfoManager
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfoManager
{
public:
	PartyInviteInfoManager() throw();
	~PartyInviteInfoManager() throw();

public:
	bool hasInviteInfo(const string& HostName) throw(Error);
	bool canInvite(Creature* pHost, Creature* pGuest) throw(Error);
	bool isInviting(Creature* pHost, Creature* pGuest) throw(Error);
	void initInviteInfo(Creature* pHost, Creature* pGuest) throw(Error);
	void cancelInvite(Creature* pHost, Creature* pGuest) throw(Error);
	void cancelInvite(Creature* pCreature) throw(Error);

public:
	bool addInviteInfo(PartyInviteInfo* pInfo) throw(Error);
	void deleteInviteInfo(const string& HostName) throw(NoSuchElementException, Error);
	PartyInviteInfo* getInviteInfo(const string& HostName) throw(NoSuchElementException, Error);

protected:
	map<string, PartyInviteInfo*> m_InfoMap;
	Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class Party
//////////////////////////////////////////////////////////////////////////////

class Party
{
public:
	Party(Creature::CreatureClass CClass) throw();
	~Party() throw();

public:
	int getID(void) const { return m_ID; }
	void setID(int ID) { m_ID = ID; }

	Creature::CreatureClass getCreatureClass(void) const { return m_CreatureClass; }

public:
	Creature* getMember(const string& name) const throw(NoSuchElementException, Error);
	void addMember(Creature* pCreature) throw(DuplicatedException, Error);
	void deleteMember(const string& name) throw(NoSuchElementException, Error);
	bool hasMember(const string& name) const throw();

	// 글로벌 파티 매니저에서만 사용한다.
	// 파티를 해체하기 전에 파티 멤버들의 파티 ID를 0으로 만들고,
	// 로컬 파티 매니저에서 해당 ID를 가진 파티를 삭제한다.
	void destroyParty(void) throw();

public:
	// 파티 멤버들에게 패킷을 날린다.
	void broadcastPacket(Packet* pPacket, Creature* pOwner=NULL) throw(ProtocolException, Error);

	// 새로운 파티원이 추가되었을 때 파티원들에게 날아가는
	// GCPartyJoined 패킷을 구성한다.
	void makeGCPartyJoined(GCPartyJoined* pGCPartyJoined) const throw();

public:
	int getSize(void) const throw();
	map<string, Creature*> getMemberMap(void) throw();

	// 근접한 거리(8타일) 내에 있는 멤버들의 숫자를 리턴한다.
	int getAdjacentMemberSize(Creature* pLeader) const throw();
	int getAdjacentMemberSize_LOCKED(Creature* pLeader) const throw();

	// 경험치를 부풀려서 나눈다.
	int shareAttrExp(Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) const throw();
	int shareVampireExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const throw();
	int shareOustersExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const throw();

public:
	void shareRevealer(Creature* pCaster, int Duration) throw(Error);
	void shareDetectHidden(Creature* pCaster, int Duration) throw(Error);
	void shareDetectInvisibility(Creature* pCaster, int Duration) throw(Error);
	void shareExpansion(Creature* pCaster, int Duration, int percent) throw(Error);
	void shareActivation(Creature* pCaster, int Duration) throw(Error);
	void shareGnomesWhisper(Creature* pCaster, int Duration, int SkillLevel) throw(Error);
	void shareHolyArmor(Creature* pCaster, int DefBonus, int SkillLevel) throw(Error);
	bool shareWaterElementalHeal(Creature* pCaster, int HealPoint) throw(Error);
	void shareGDRLairEnter(Creature* pLeader) throw(Error);

	void shareRankExp(Creature* pLeader, int amount) throw();
	void shareAdvancementExp(Creature* pLeader, int amount) throw();

	void dissectCorpse(Creature* pDissecter, MonsterCorpse* pCorpse) throw(Error);
	void eventPartyCrash() throw(Error);

public:
	bool isFamilyPay() const { return m_bFamilyPay; }
	void refreshFamilyPay();

public:
	string toString(void) const throw();

protected:
	int                          m_ID;            // 파티 ID
	Creature::CreatureClass      m_CreatureClass; // 파티의 종류
	map<string, Creature*>  m_MemberMap;     // 파티 멤버
	mutable Mutex                m_Mutex;         // 내부에서 쓰는 락
	bool						 m_bFamilyPay;	  // 패밀리 요금제 적용 파티인가?
};


//////////////////////////////////////////////////////////////////////////////
// class PartyManager
//////////////////////////////////////////////////////////////////////////////

class PartyManager
{
public:
	PartyManager() throw();
	virtual ~PartyManager() throw();

public:
	virtual bool createParty(int ID, Creature::CreatureClass) throw(DuplicatedException, Error);
	virtual bool addPartyMember(int ID, Creature* pCreature) throw(NoSuchElementException, DuplicatedException, Error);
	virtual bool deletePartyMember(int ID, Creature* pCreature) throw(NoSuchElementException, Error);
	virtual Party* getParty(int ID) throw(NoSuchElementException, Error);

public:
	virtual string toString(void) const throw() = 0;

protected:
	map<int, Party*> m_PartyMap; // 파티 집합
	mutable Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class LocalPartyManager
//////////////////////////////////////////////////////////////////////////////

class LocalPartyManager : public PartyManager
{
public:
	LocalPartyManager() throw();
	virtual ~LocalPartyManager() throw();

public:
	void heartbeat(void) throw(Error);
	int getAdjacentMemberSize(int PartyID, Creature* pLeader) const throw();
	int shareAttrExp(int PartyID, Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) const throw();
	int shareVampireExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const throw();
	int shareOustersExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const throw();
	void shareRevealer(int PartyID, Creature* pCaster, int Duration) throw(Error);
	void shareDetectHidden(int PartyID, Creature* pCaster, int Duration) throw(Error);
	void shareDetectInvisibility(int PartyID, Creature* pCaster, int Duration) throw(Error);
	void shareExpansion(int PartyID, Creature* pCaster, int Duration, int Percent) throw(Error);
	void shareActivation(int PartyID, Creature* pCaster, int Duration) throw(Error);
	void shareGnomesWhisper(int PartyID, Creature* pCaster, int Duration, int SkillLevel) throw(Error);
	void shareHolyArmor(int PartyID, Creature* pCaster, int DefBonus, int SkillLevel) throw(Error);
	bool shareWaterElementalHeal(int PartyID, Creature* pCaster, int HealPoint) throw(Error);
	void shareGDRLairEnter(int PartyID, Creature* pLeader) throw(Error);
	
	int shareRankExp(int PartyID, Creature* pLeader, int amount) const throw();
	int shareAdvancementExp(int PartyID, Creature* pLeader, int amount) const throw();

public:
	virtual string toString(void) const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class GlobalPartyManager
//////////////////////////////////////////////////////////////////////////////

class GlobalPartyManager : public PartyManager
{
public:
	GlobalPartyManager() throw();
	virtual ~GlobalPartyManager() throw();

public:
	bool canAddMember(int ID) throw(NoSuchElementException, Error);
	virtual bool addPartyMember(int ID, Creature* pCreature) throw(NoSuchElementException, DuplicatedException, Error);
	virtual bool deletePartyMember(int ID, Creature* pCreature) throw(NoSuchElementException, Error);
	virtual bool expelPartyMember(int ID, Creature* pExpeller, const string& ExpelleeName) throw(NoSuchElementException, Error);

	int registerParty(void) throw(Error);

	void refreshFamilyPay(int ID);

public:
	virtual string toString(void) const throw();

protected:
	int m_PartyIDRegistry; // 파티 ID 생성자
};

extern GlobalPartyManager* g_pGlobalPartyManager;


//////////////////////////////////////////////////////////////////////////////
// 편의를 위한 전역 함수들...
//////////////////////////////////////////////////////////////////////////////
void deleteAllPartyInfo(Creature* pCreature) throw();


#endif
