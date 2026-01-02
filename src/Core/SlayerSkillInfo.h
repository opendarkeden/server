//////////////////////////////////////////////////////////////////////
// 
// Filename    : SlayerSkillInfo.h 
// Written By  : elca@ewestsoft.com
// Description :  Slayer skill information
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
// Holds a Slayer's skill information to be delivered to the client.
//
//////////////////////////////////////////////////////////////////////

class SlayerSkillInfo : public PCSkillInfo {

public :
	
	// constructor
	SlayerSkillInfo () ;
	
	// destructor
	~SlayerSkillInfo () noexcept ;

public :

	// Initialize the packet by reading data from the input stream.
    virtual void read (SocketInputStream & iStream) ;
		    
	// Serialize the packet into the output stream.
    virtual void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// Serialized size varies with the contained skill list.
	PacketSize_t getSize () ;

	static uint getMaxSize ()  { 
		return szBYTE + szSkillDomainType + szBYTE + (SubSlayerSkillInfo::getMaxSize()* 255);
	}

	// get packet's debug string
	string toString () const ;

	// get / set New Skill
	bool isLearnNewSkill() const  { return m_bLearnNewSkill; }
	void setLearnNewSkill(bool NewSkill)  { m_bLearnNewSkill = NewSkill; }

	// get /set DomainType
	SkillDomainType_t getDomainiType() const  { return m_DomainType; }
	void setDomainType(SkillDomainType_t DomainType) { m_DomainType = DomainType; }

	// get / set ListNumber
	BYTE getListNum() const  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(SubSlayerSkillInfo* pSubSlayerSkillInfo)  { m_SubSlayerSkillInfoList.push_back(pSubSlayerSkillInfo); }

	// ClearList
	void clearList()  { m_SubSlayerSkillInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubSlayerSkillInfo* popFrontListElement()  
	{ 
		SubSlayerSkillInfo* TempSubSlayerSkillInfo = m_SubSlayerSkillInfoList.front(); m_SubSlayerSkillInfoList.pop_front(); return TempSubSlayerSkillInfo; 
	}

private :

	// Tracks whether there is a newly learnable skill
	bool m_bLearnNewSkill;

	SkillDomainType_t m_DomainType;
	
	// SubSlayerSkillInfo List Total Number
	BYTE m_ListNum;

	// SubSlayerSkillInfo List
	list<SubSlayerSkillInfo*> m_SubSlayerSkillInfoList;

};

#endif
