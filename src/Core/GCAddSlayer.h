//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlayer.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_SLAYER_H__
#define __GC_ADD_SLAYER_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayer;
// 로그인이나 포탈, 텔레포트 등으로 슬레이어가 존에 새로 들어갔을 경우, 또는 
// 슬레이어가 존에서 이동할 경우,(1) 이미 이 슬레이어에 대한 정보를 갖고 있는 
//(즉 이 슬레이어를 보고 있는..) 영역에 존재하는 PC들에게는 GCMove 패킷을 
// 브로드캐스트한다. 그러나,(2) 이 슬레이어를 처음 보게 되는 영역에 존재하는 
// PC들에게는 GCAddSlayer 패킷을 브로드캐스트한다. 또한,(3) 이 슬레이어는 
// 자신이 새로 개척한 시야(?) 안에 존재하는 슬레이어들의 정보를 GCAddSlayer에 
// 담아서 받게 된다.
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayer : public Packet 
{
public:
	GCAddSlayer();
	GCAddSlayer(const PCSlayerInfo3 & slayerInfo);
	virtual ~GCAddSlayer() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCAddSlayer"; }
	string toString() const throw();

public:
	PCSlayerInfo3 & getSlayerInfo() throw() { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo() const throw() { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo) throw() { m_SlayerInfo = slayerInfo; }

	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo() const throw() { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo() const throw() { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

private:
	PCSlayerInfo3  m_SlayerInfo;  // 슬레이어의 외모 정보
	EffectInfo*    m_pEffectInfo; // 걸려있는 이펙트 정보
	PetInfo*	   m_pPetInfo;	  // 펫 관련 정보
	NicknameInfo*	   m_pNicknameInfo;	  // 펫 관련 정보
	StoreOutlook		m_StoreOutlook;	// 개인상점 관련 정보
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddSlayer(); }
	string getPacketName() const throw() { return "GCAddSlayer"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return PCSlayerInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerHandler 
{
public:
	static void execute(GCAddSlayer* pPacket, Player* pPlayer) throw(Error);
};

#endif
