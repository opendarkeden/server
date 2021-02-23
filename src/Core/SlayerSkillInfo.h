//////////////////////////////////////////////////////////////////////
// 
// Filename    : SlayerSkillInfo.h 
// Written By  : elca@ewestsoft.com
// Description :  스킬의 정보들
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_SKILL_INFO_H__
#define __SLAYER_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PCSkillInfo.h"
#include "SubSlayerSkillInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class SlayerSkillInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class SlayerSkillInfo : public PCSkillInfo {

public :
	
	// constructor
	SlayerSkillInfo () throw ();
	
	// destructor
	~SlayerSkillInfo () throw ();

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    virtual void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () { 
		return szBYTE + szSkillDomainType + szBYTE + (SubSlayerSkillInfo::getMaxSize()* 255);
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set New Skill
	bool isLearnNewSkill() const throw() { return m_bLearnNewSkill; }
	void setLearnNewSkill(bool NewSkill) throw() { m_bLearnNewSkill = NewSkill; }

	// get /set DomainType
	SkillDomainType_t getDomainiType() const throw() { return m_DomainType; }
	void setDomainType(SkillDomainType_t DomainType) { m_DomainType = DomainType; }

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(SubSlayerSkillInfo* pSubSlayerSkillInfo) throw() { m_SubSlayerSkillInfoList.push_back(pSubSlayerSkillInfo); }

	// ClearList
	void clearList() throw() { m_SubSlayerSkillInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubSlayerSkillInfo* popFrontListElement() throw() 
	{ 
		SubSlayerSkillInfo* TempSubSlayerSkillInfo = m_SubSlayerSkillInfoList.front(); m_SubSlayerSkillInfoList.pop_front(); return TempSubSlayerSkillInfo; 
	}

private :

	// New 스킬을 배울 수 있느냐 없느냐 정보
	bool m_bLearnNewSkill;

	SkillDomainType_t m_DomainType;
	
	// SubSlayerSkillInfo List Total Number
	BYTE m_ListNum;

	// SubSlayerSkillInfo List
	list<SubSlayerSkillInfo*> m_SubSlayerSkillInfoList;

};

#endif
