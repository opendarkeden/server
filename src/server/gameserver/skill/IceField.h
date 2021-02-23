//////////////////////////////////////////////////////////////////////////////
// Filename    : IceField.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_FIELD_HANDLER_H__
#define __SKILL_ICE_FIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceField;
//////////////////////////////////////////////////////////////////////////////

class IceField : public SkillHandler 
{
public:
	IceField() throw();
	~IceField() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IceField"; }
	SkillType_t getSkillType() const throw() { return SKILL_ICE_FIELD; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT		m_IceFieldMask[4][9];	// 4단계, 9개씩
	int			m_MaskNum[4];
};

// global variable declaration
extern IceField g_IceField;

#endif // __SKILL_ICE_FIELD_HANDLER_H__
