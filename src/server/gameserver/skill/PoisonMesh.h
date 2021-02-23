//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonMesh.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISON_MESH_HANDLER_H__
#define __SKILL_POISON_MESH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonMesh;
//////////////////////////////////////////////////////////////////////////////

class PoisonMesh: public SkillHandler 
{
public:
	PoisonMesh() throw() {}
	~PoisonMesh() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PoisonMesh"; }
	SkillType_t getSkillType() const throw() { return SKILL_POISON_MESH; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonMesh g_PoisonMesh;

#endif // __SKILL_POISON_MESH_HANDLER_H__
