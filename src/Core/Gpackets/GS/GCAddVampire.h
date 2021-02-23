//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampire.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_VAMPIRE_H__
#define __GC_ADD_VAMPIRE_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampire;
//
// 로그인이나 포탈, 텔레포트 등으로 슬레이어가 존에 새로 들어갔을 경우, 또는
// 슬레이어가 존에서 이동할 경우,(1) 이미 이 슬레이어에 대한 정보를 갖고 있는
//(즉 이 슬레이어를 보고 있는..) 영역에 존재하는 PC들에게는 GCMove 패킷을
// 브로드캐스트한다. 그러나,(2) 이 슬레이어를 처음 보게 되는 영역에 존재하는
// PC들에게는 GCAddVampire 패킷을 브로드캐스트한다. 또한,(3) 이 슬레이어는
// 자신이 새로 개척한 시야(?) 안에 존재하는 슬레이어들의 정보를 GCAddVampire에
// 담아서 받게 된다.
//////////////////////////////////////////////////////////////////////////////

class GCAddVampire : public Packet 
{
public:
	GCAddVampire() throw() : m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	GCAddVampire(const PCVampireInfo3 & vampireInfo) throw() : m_VampireInfo(vampireInfo), m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	virtual ~GCAddVampire() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_VAMPIRE; }
	PacketSize_t getPacketSize() const throw()
	{
		PacketSize_t ret = m_VampireInfo.getSize() + m_pEffectInfo->getSize() + ((m_pPetInfo!=NULL)?m_pPetInfo->getSize():szPetType) + szBYTE;

		if ( m_pNicknameInfo == NULL )
		{
			NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			ret += noNick.getSize();
		}
		else
		{
			ret += m_pNicknameInfo->getSize();
		}

		ret += m_StoreOutlook.getSize();

		return ret;
	}
	string getPacketName() const throw() { return "GCAddVampire"; }
	string toString() const throw();

public:
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const throw() { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) throw() { m_VampireInfo = vampireInfo; }

	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo() const throw() { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo() const throw() { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

	BYTE getFromFlag(void) const { return m_FromFlag; }
	void setFromFlag(BYTE flag) { m_FromFlag = flag; }

private:
	PCVampireInfo3 m_VampireInfo; // 뱀파이어 외모 정보
	EffectInfo*    m_pEffectInfo; // 이펙트 정보
	PetInfo*	   m_pPetInfo;	  // 펫 정보
	NicknameInfo*	   m_pNicknameInfo;	  // 펫 정보
	StoreOutlook		m_StoreOutlook;	// 개인상점 정보
	BYTE           m_FromFlag;    // 어디로부터인가? 정상일 경우에는 0, 포탈을 통했을 경우에는 1
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddVampire(); }
	string getPacketName() const throw() { return "GCAddVampire"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_VAMPIRE; }
	PacketSize_t getPacketMaxSize() const throw() { return PCVampireInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize() + szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireHandler 
{
public:
	static void execute(GCAddVampire* pPacket, Player* pPlayer) throw(Error);

};

#endif
