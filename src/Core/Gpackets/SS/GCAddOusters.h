//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddOusters.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_OUSTERS_H__
#define __GC_ADD_OUSTERS_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCOustersInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddOusters;
// 로그인이나 포탈, 텔레포트 등으로 슬레이어가 존에 새로 들어갔을 경우, 또는 
// 슬레이어가 존에서 이동할 경우,(1) 이미 이 슬레이어에 대한 정보를 갖고 있는 
//(즉 이 슬레이어를 보고 있는..) 영역에 존재하는 PC들에게는 GCMove 패킷을 
// 브로드캐스트한다. 그러나,(2) 이 슬레이어를 처음 보게 되는 영역에 존재하는 
// PC들에게는 GCAddOusters 패킷을 브로드캐스트한다. 또한,(3) 이 슬레이어는 
// 자신이 새로 개척한 시야(?) 안에 존재하는 슬레이어들의 정보를 GCAddOusters에 
// 담아서 받게 된다.
// 멍~~
//////////////////////////////////////////////////////////////////////////////

class GCAddOusters : public Packet 
{
public:
	GCAddOusters();
	GCAddOusters(const PCOustersInfo3 & slayerInfo);
	virtual ~GCAddOusters() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_OUSTERS; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCAddOusters"; }
	string toString() const throw();

public:
	PCOustersInfo3 & getOustersInfo() throw() { return m_OustersInfo; }
	const PCOustersInfo3 & getOustersInfo() const throw() { return m_OustersInfo; }
	void setOustersInfo(const PCOustersInfo3 & slayerInfo) throw() { m_OustersInfo = slayerInfo; }

	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo() const throw() { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo() const throw() { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

private:
	PCOustersInfo3  m_OustersInfo;  // 슬레이어의 외모 정보
	EffectInfo*    m_pEffectInfo; // 걸려있는 이펙트 정보
	PetInfo*    m_pPetInfo; // 걸려있는 이펙트 정보
	NicknameInfo*	m_pNicknameInfo;
	StoreOutlook	m_StoreOutlook;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddOustersFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddOustersFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddOusters(); }
	string getPacketName() const throw() { return "GCAddOusters"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_OUSTERS; }
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return PCOustersInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddOustersHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddOustersHandler 
{
public:
	static void execute(GCAddOusters* pPacket, Player* pPlayer) throw(Error);
};

#endif
