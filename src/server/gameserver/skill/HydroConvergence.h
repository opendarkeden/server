//////////////////////////////////////////////////////////////////////////////
// Filename    : HydroConvergence.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HYDRO_CONVERGENCE_HANDLER_H__
#define __SKILL_HYDRO_CONVERGENCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HydroConvergence;
//////////////////////////////////////////////////////////////////////////////

class HydroConvergence: public SkillHandler 
{
public:
	HydroConvergence() throw() {}
	~HydroConvergence() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HydroConvergence"; }

	SkillType_t getSkillType() const throw() { return SKILL_HYDRO_CONVERGENCE; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HydroConvergence g_HydroConvergence;

#endif // __SKILL_HYDRO_CONVERGENCE_HANDLER_H__
