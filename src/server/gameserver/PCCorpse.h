//////////////////////////////////////////////////////////////////////////////
// Filename    : PCCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_CORPSE_H__
#define __PC_CORPSE_H__

#include "Corpse.h"

//////////////////////////////////////////////////////////////////////////////
// class PCCorpse;
// PC 가 죽은 경우, 남기는 시체다.
//////////////////////////////////////////////////////////////////////////////

class PCCorpse : public Corpse 
{
// methods from Object
public:
	virtual string toString() const throw();

// methods from Item
public:
	// 크리처의 인벤토리에서 아이템을 꺼내서, 시체에 집어넣는다.
	void transportItems(Creature* pCreature) throw(Error);

// data members
private:
	// PC 시체에서 구별가능한 것들은 무엇이 있을까?
	// 헤어스타일 - 머리색 - 피부색 - 머리 - 상의 - 하의 - 무기1 - 무기2
	HairStyle m_HairStyle;
	Color_t   m_HairColor;
	Color_t   m_SkinColor;
	Color_t   m_UpperColors[2];
	Color_t   m_LowerColors[2];
	
};

#endif
