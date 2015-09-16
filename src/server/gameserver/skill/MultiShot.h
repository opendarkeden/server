//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiShot.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_SHOT_HANDLER_H__
#define __SKILL_MULTI_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiShot;
//////////////////////////////////////////////////////////////////////////////

class MultiShot : public SkillHandler 
{
public:
	MultiShot() throw();
	~MultiShot() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MultiShot"; }
	SkillType_t getSkillType() const throw() { return SKILL_MULTI_SHOT; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	void SGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void ARSMGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

protected:
	POINT m_pSGMask[8];    // SG 마스크는 방향과는 관계가 없다.
	POINT m_pARMask[8][3]; // AR, SMG마스크는 방향과 관계가 있다.
};

// global variable declaration
extern MultiShot g_MultiShot;

#endif // __SKILL_MULTI_SHOT_H__
