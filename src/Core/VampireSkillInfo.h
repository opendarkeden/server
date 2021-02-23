//////////////////////////////////////////////////////////////////////
// 
// Filename    : VampireSkillInfo.h 
// Written By  : elca@ewestsoft.com
// Description :  스킬의 정보들
// 
//////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_SKILL_INFO_H__
#define __VAMPIRE_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PCSkillInfo.h"
#include "SubVampireSkillInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class VampireSkillInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class VampireSkillInfo : public PCSkillInfo {

public :
	
	// constructor
	VampireSkillInfo () throw ();
	
	// destructor
	~VampireSkillInfo () throw ();

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () { 
		return szBYTE + szBYTE + (SubVampireSkillInfo::getMaxSize()* 120);
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
	void addListElement(SubVampireSkillInfo* pSubVampireSkillInfo) throw() { m_SubVampireSkillInfoList.push_back(pSubVampireSkillInfo); }

	// ClearList
	void clearList() throw() { m_SubVampireSkillInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubVampireSkillInfo* popFrontListElement() throw() 
	{ 
		SubVampireSkillInfo* TempSubVampireSkillInfo = m_SubVampireSkillInfoList.front(); m_SubVampireSkillInfoList.pop_front(); return TempSubVampireSkillInfo; 
	}

private :

	// New 스킬을 배울 수 있느냐 없느냐 정보
	bool m_bLearnNewSkill;

	// SubVampireSkillInfo List Total Number
	BYTE m_ListNum;

	// SubVampireSkillInfo List
	list<SubVampireSkillInfo*> m_SubVampireSkillInfoList;

};

#endif
