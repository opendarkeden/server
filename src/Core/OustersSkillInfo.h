//////////////////////////////////////////////////////////////////////
// 
// Filename    : OustersSkillInfo.h 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_SKILL_INFO_H__
#define __OUSTERS_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PCSkillInfo.h"
#include "SubOustersSkillInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class OustersSkillInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class OustersSkillInfo : public PCSkillInfo {

public :
	
	// constructor
	OustersSkillInfo () throw ();
	
	// destructor
	~OustersSkillInfo () throw ();

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () { 
		return szBYTE + szBYTE + (SubOustersSkillInfo::getMaxSize()* 120);
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set New Skill
	bool isLearnNewSkill() const throw() { return m_bLearnNewSkill; }
	void setLearnNewSkill(bool NewSkill) throw() { m_bLearnNewSkill = NewSkill; }

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(SubOustersSkillInfo* pSubOustersSkillInfo) throw() { m_SubOustersSkillInfoList.push_back(pSubOustersSkillInfo); }

	// ClearList
	void clearList() throw() { m_SubOustersSkillInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubOustersSkillInfo* popFrontListElement() throw() 
	{ 
		SubOustersSkillInfo* TempSubOustersSkillInfo = m_SubOustersSkillInfoList.front(); m_SubOustersSkillInfoList.pop_front(); return TempSubOustersSkillInfo; 
	}

private :

	// New 스킬을 배울 수 있느냐 없느냐 정보
	bool m_bLearnNewSkill;

	// SubOustersSkillInfo List Total Number
	BYTE m_ListNum;

	// SubOustersSkillInfo List
	list<SubOustersSkillInfo*> m_SubOustersSkillInfoList;

};

#endif
